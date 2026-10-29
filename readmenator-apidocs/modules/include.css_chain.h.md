# `include/css_chain.h`

> Source: [include/css_chain.h:1](../../include/css_chain.h#L1) | language `h` | coverage 25.0% | [API index](../index.md)

## Contents

- **Structs:** [`cvr_chain`](#cvr_chain), [`cvr_table`](#cvr_table)
- **Type Aliases:** [`cch_path`](#cch_path)
- **Functions:** [`cch_path_new`](#cch_path_new), [`cch_path_free`](#cch_path_free), [`cch_element_matches`](#cch_element_matches), [`lacks`](#lacks), [`box`](#box)
- **Macros:** [`CCH_CHAIN_MAX`](#cch_chain_max), [`CCH_SIB_MAX`](#cch_sib_max), [`CCH_NTH_MAX`](#cch_nth_max)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class cvr_chain
    <<struct>> cvr_chain
    class cvr_table
    <<struct>> cvr_table
    class cch_path
    <<type_alias>> cch_path
```

## Structs

<a id="cvr_chain"></a>

### `cvr_chain`

`struct` | [include/css_chain.h:51](../../include/css_chain.h#L51)

```c
struct cvr_chain;
```

---

<a id="cvr_table"></a>

### `cvr_table`

`struct` | [include/css_chain.h:52](../../include/css_chain.h#L52)

```c
struct cvr_table;
```

---

## Type Aliases

<a id="cch_path"></a>

### `cch_path`

`type_alias` | [include/css_chain.h:69](../../include/css_chain.h#L69)

```c
typedef struct cch_path cch_path;
```

A persistent root->element path shared by consecutive resolutions in ONE build over a document that does not change meanwhile (spec/css_chain.md). cch_element_style_path is cch_element_style_vars with the ancestor chain reused from the previous call instead of rebuilt; the result is identical. pa == NULL (or a chain deeper than CCH_CHAIN_MAX) takes the uncached route.

The path must not outlive a DOM mutation: free it when the build ends.

---

## Functions

<a id="cch_path_new"></a>

### `cch_path_new`

`function` | [include/css_chain.h:70](../../include/css_chain.h#L70)

```c
cch_path *cch_path_new(void);
```

**Returns:** `cch_path *`

*Called by:* [`PV_STYLE_RESERVE_MAX`](src.page_view.c.md#pv_style_reserve_max)

---

<a id="cch_path_free"></a>

### `cch_path_free`

`function` | [include/css_chain.h:71](../../include/css_chain.h#L71)

```c
void cch_path_free(cch_path *pa);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pa` | `cch_path *` |  |  |

*Called by:* [`PV_STYLE_RESERVE_MAX`](src.page_view.c.md#pv_style_reserve_max)

---

<a id="cch_element_matches"></a>

### `cch_element_matches`

`function` | [include/css_chain.h:81](../../include/css_chain.h#L81)

```c
int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel);
```

Nonzero iff the parsed selector *sel matches element `el`, built against the same bounded ancestor/sibling/attribute context as cch_element_style.

This is the single source of truth for selector matching: the DOM's querySelector and the author-CSS cascade agree by construction. `sel` is a pre-parsed css_sel (see csel_parse); NULL args return 0 (fail closed).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `el` | `lxb_dom_element_t *` |  |  |
| `sel` | `css_sel *` |  |  |

**Returns:** `int`

*Called by:* [`attributes`](src.page_view.c.md#attributes)

---

<a id="lacks"></a>

### `lacks`

`function` | [include/css_chain.h:85](../../include/css_chain.h#L85)

```c
* the element lacks (csel's subj_req) is rejected before the ancestor chain is built: on a * query that scans a whole document nearly every candidate dies there, so the scan no longer * pays O(depth)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `subj_req` | `csel's` |  |  |

**Returns:** `* the element`

---

<a id="box"></a>

### `box`

`function` | [include/css_chain.h:91](../../include/css_chain.h#L91)

```c
* generated box (css_resolve_pseudo) against the same element context. * font_size is el's own COMPUTED font-size (the pseudo inherits it) and * inherited el's own custom-property chain (NULL = none).
```

**Returns:** `* generated`

---

## Macros

<a id="cch_chain_max"></a>

### `CCH_CHAIN_MAX`

`macro` | [include/css_chain.h:26](../../include/css_chain.h#L26)

```c
#define CCH_CHAIN_MAX
```

Bounds (anti-DoS; beyond each the context reads unknown/absent, fail closed): ancestors carried for combinator matching, preceding siblings carried for the subject's `+`/`~`, and the sibling-position walk cap.

---

<a id="cch_sib_max"></a>

### `CCH_SIB_MAX`

`macro` | [include/css_chain.h:27](../../include/css_chain.h#L27)

```c
#define CCH_SIB_MAX
```

---

<a id="cch_nth_max"></a>

### `CCH_NTH_MAX`

`macro` | [include/css_chain.h:28](../../include/css_chain.h#L28)

```c
#define CCH_NTH_MAX
```

---
