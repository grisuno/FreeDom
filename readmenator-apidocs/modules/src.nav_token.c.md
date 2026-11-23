# `src/nav_token.c`

> Source: [src/nav_token.c:1](../../src/nav_token.c#L1) | language `c` | coverage 9.1% | [API index](../index.md)

nav_token -- per-tab navigation identity shared with fetch threads. spec/nav_token.md

## Contents

- **Structs:** [`nt_token`](#nt_token)
- **Functions:** [`nt_new`](#nt_new), [`nt_ref`](#nt_ref), [`nt_unref`](#nt_unref), [`nt_cancel`](#nt_cancel), [`nt_cancelled`](#nt_cancelled), [`nt_set_foreground`](#nt_set_foreground), [`nt_foreground`](#nt_foreground), [`nt_id`](#nt_id), [`nt_route`](#nt_route)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_nav_token_c__nt_route(["nt_route"])
    n_src_nav_token_c__nt_cancelled(["nt_cancelled"])
    n_src_nav_token_c__nt_route --> n_src_nav_token_c__nt_cancelled
```

## Structs

<a id="nt_token"></a>

### `nt_token`

`struct` | [src/nav_token.c:7](../../src/nav_token.c#L7)

```c
struct nt_token
```

---

## Functions

<a id="nt_new"></a>

### `nt_new`

`function` | [src/nav_token.c:16](../../src/nav_token.c#L16)

```c
nt_token *nt_new(void)
```

**Returns:** `nt_token *`

---

<a id="nt_ref"></a>

### `nt_ref`

`function` | [src/nav_token.c:26](../../src/nav_token.c#L26)

```c
nt_token *nt_ref(nt_token *t)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `nt_token *` |  |  |

**Returns:** `nt_token *`

---

<a id="nt_unref"></a>

### `nt_unref`

`function` | [src/nav_token.c:31](../../src/nav_token.c#L31)

```c
void nt_unref(nt_token **tp)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `tp` | `nt_token **` |  |  |

---

<a id="nt_cancel"></a>

### `nt_cancel`

`function` | [src/nav_token.c:38](../../src/nav_token.c#L38)

```c
void nt_cancel(nt_token *t)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `nt_token *` |  |  |

---

<a id="nt_cancelled"></a>

### `nt_cancelled`

`function` | [src/nav_token.c:42](../../src/nav_token.c#L42)

```c
int nt_cancelled(const nt_token *t)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `nt_token *` |  |  |

**Returns:** `int`

*Called by:* [`nt_route`](#nt_route)

---

<a id="nt_set_foreground"></a>

### `nt_set_foreground`

`function` | [src/nav_token.c:47](../../src/nav_token.c#L47)

```c
void nt_set_foreground(nt_token *t, int on)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `nt_token *` |  |  |
| `on` | `int` |  |  |

---

<a id="nt_foreground"></a>

### `nt_foreground`

`function` | [src/nav_token.c:51](../../src/nav_token.c#L51)

```c
int nt_foreground(const nt_token *t)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `nt_token *` |  |  |

**Returns:** `int`

---

<a id="nt_id"></a>

### `nt_id`

`function` | [src/nav_token.c:56](../../src/nav_token.c#L56)

```c
uint64_t nt_id(const nt_token *t)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `nt_token *` |  |  |

**Returns:** `uint64_t`

---

<a id="nt_route"></a>

### `nt_route`

`function` | [src/nav_token.c:58](../../src/nav_token.c#L58)

```c
nt_route_kind nt_route(const nt_token *job, const nt_token *active, nt_token *const *parked, int n, int *slot)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `job` | `nt_token *` |  |  |
| `active` | `nt_token *` |  |  |
| `parked` | `nt_token *const *` |  |  |
| `n` | `int` |  |  |
| `slot` | `int *` |  |  |

*Calls:* [`nt_cancelled`](#nt_cancelled)

*Called by:* [`LLVMFuzzerTestOneInput`](fuzz.fuzz_nav_token.c.md#llvmfuzzertestoneinput)

---
