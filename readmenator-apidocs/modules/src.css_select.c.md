# `src/css_select.c`

> Source: [src/css_select.c:1](../../src/css_select.c#L1) | language `c` | coverage 65.0% | [API index](../index.md)

## Contents

- **Functions:** [`csel_hex_val`](#csel_hex_val), [`csel_emit_utf8`](#csel_emit_utf8), [`csel_unescape`](#csel_unescape), [`csel_escape_len`](#csel_escape_len), [`csel_decl_end`](#csel_decl_end), [`csel_ident_fold`](#csel_ident_fold), [`csel_ident_eq`](#csel_ident_eq), [`csel_read_ident`](#csel_read_ident), [`between`](#between), [`selector`](#selector), [`csel_element_feature_bits`](#csel_element_feature_bits), [`seven`](#seven), [`csel_compact_size`](#csel_compact_size), [`csel_compact_dup`](#csel_compact_dup), [`csel_parse`](#csel_parse), [`built`](#built), [`csel_needs_structure`](#csel_needs_structure), [`csel_matches`](#csel_matches)
- **Macros:** [`HAS_MAX_DEPTH`](#has_max_depth)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_css_select_c__csel_unescape(["csel_unescape"])
    n_src_css_select_c__csel_emit_utf8(["csel_emit_utf8"])
    n_src_css_select_c__csel_hex_val(["csel_hex_val"])
    n_src_css_select_c__csel_escape_len(["csel_escape_len"])
    n_src_css_select_c__csel_ident_eq(["csel_ident_eq"])
    n_src_css_select_c__csel_ident_fold(["csel_ident_fold"])
    n_src_css_select_c__csel_read_ident(["csel_read_ident"])
    n_src_css_select_c__selector(["selector"])
    n_src_css_select_c__csel_compact_dup(["csel_compact_dup"])
    n_src_css_select_c__csel_compact_size(["csel_compact_size"])
    n_gui_browser_ui_c__strcmp["browser_ui.strcmp"]
    n_include_css_select_h__csel_ident_ch["css_select.csel_ident_ch"]
    n_include_css_select_h__csel_lower_ch["css_select.csel_lower_ch"]
    n_src_css_select_c__csel_unescape --> n_src_css_select_c__csel_emit_utf8
    n_src_css_select_c__csel_unescape --> n_src_css_select_c__csel_hex_val
    n_src_css_select_c__csel_escape_len --> n_src_css_select_c__csel_hex_val
    n_src_css_select_c__csel_ident_eq --> n_src_css_select_c__csel_ident_fold
    n_src_css_select_c__csel_read_ident --> n_src_css_select_c__csel_escape_len
    n_src_css_select_c__csel_read_ident --> n_src_css_select_c__csel_ident_fold
    n_src_css_select_c__csel_read_ident --> n_src_css_select_c__csel_unescape
    n_src_css_select_c__selector --> n_src_css_select_c__csel_ident_fold
    n_src_css_select_c__csel_compact_dup --> n_src_css_select_c__csel_compact_size
    n_src_css_select_c__csel_ident_eq -.-> n_gui_browser_ui_c__strcmp
    n_src_css_select_c__csel_read_ident -.-> n_include_css_select_h__csel_ident_ch
    n_src_css_select_c__csel_read_ident -.-> n_include_css_select_h__csel_lower_ch
```

## Functions

<a id="csel_hex_val"></a>

### `csel_hex_val`

`function` | [src/css_select.c:25](../../src/css_select.c#L25)

```c
int csel_hex_val(char c)
```

CSS Syntax 4.3.7 escape consumption (moved from css.c; shared by quoted content values and selector identifiers).

Backslash + 1-6 hex digits (then one optional whitespace, eaten as the terminator) is the codepoint, emitted UTF-8; backslash + newline eats both (continuation); backslash + anything else is that char; a trailing backslash is dropped. Null, surrogates and > U+10FFFF become U+FFFD. Decoded output only ever shrinks, except \0-like escapes (2 chars -> 3 bytes), so the write is capped and a hostile value truncates instead of overflowing.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `char` |  |  |

**Returns:** `int`

*Called by:* [`csel_escape_len`](#csel_escape_len), [`csel_unescape`](#csel_unescape)

---

<a id="csel_emit_utf8"></a>

### `csel_emit_utf8`

`function` | [src/css_select.c:32](../../src/css_select.c#L32)

```c
size_t csel_emit_utf8(unsigned int cp, char *out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cp` | `unsigned int` |  |  |
| `out` | `char *` |  |  |

**Returns:** `size_t`

*Called by:* [`csel_unescape`](#csel_unescape)

---

<a id="csel_unescape"></a>

### `csel_unescape`

`function` | [src/css_select.c:54](../../src/css_select.c#L54)

```c
void csel_unescape(char *dst, size_t cap, const char *src, size_t n)
```

Decodes CSS escapes in src[0,n) into dst (cap bytes, NUL-terminated, truncates).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dst` | `char *` |  |  |
| `cap` | `size_t` |  |  |
| `src` | `char *` |  |  |
| `n` | `size_t` |  |  |

> **Inherited:** Documentation from [`csel_unescape`](#csel_unescape) (include/css_select.h:221).

*Calls:* [`csel_emit_utf8`](#csel_emit_utf8), [`csel_hex_val`](#csel_hex_val)

*Called by:* [`csel_read_ident`](#csel_read_ident)

---

<a id="csel_escape_len"></a>

### `csel_escape_len`

`function` | [src/css_select.c:93](../../src/css_select.c#L93)

```c
size_t csel_escape_len(const char *s, size_t i, size_t b)
```

Bytes the escape starting at s[i] occupies (0 when s[i] does not start one).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |
| `i` | `size_t` |  |  |
| `b` | `size_t` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`csel_escape_len`](#csel_escape_len) (include/css_select.h:223).

*Calls:* [`csel_hex_val`](#csel_hex_val)

*Called by:* [`csel_read_ident`](#csel_read_ident)

---

<a id="csel_decl_end"></a>

### `csel_decl_end`

`function` | [src/css_select.c:106](../../src/css_select.c#L106)

```c
size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace)
```

Index of the ';' ending the declaration that starts at s[i] (or of a '}' when stop_brace), or b: separators inside quotes, inside (...) such as url(data:a;b), or escaped, are not separators (CSS Syntax 5 section 5.4.4).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |
| `i` | `size_t` |  |  |
| `b` | `size_t` |  |  |
| `stop_brace` | `int` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`csel_decl_end`](#csel_decl_end) (include/css_select.h:235).

---

<a id="csel_ident_fold"></a>

### `csel_ident_fold`

`function` | [src/css_select.c:129](../../src/css_select.c#L129)

```c
void csel_ident_fold(const char *src, size_t len, char *dst)
```

dst (CSS_TOK_MAX bytes) receives src[0,len) as-is, or folded when too long.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `src` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `dst` | `char *` |  |  |

> **Inherited:** Documentation from [`csel_ident_fold`](#csel_ident_fold) (include/css_select.h:225).

*Called by:* [`csel_ident_eq`](#csel_ident_eq), [`csel_read_ident`](#csel_read_ident), [`selector`](#selector)

---

<a id="csel_ident_eq"></a>

### `csel_ident_eq`

`function` | [src/css_select.c:144](../../src/css_select.c#L144)

```c
int csel_ident_eq(const char *stored, const char *tok, size_t tlen)
```

A stored (possibly folded) identifier against an element token of tlen bytes.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `stored` | `char *` |  |  |
| `tok` | `char *` |  |  |
| `tlen` | `size_t` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`csel_ident_eq`](#csel_ident_eq) (include/css_select.h:227).

*Calls:* [`strcmp`](gui.browser_ui.c.md#strcmp), [`csel_ident_fold`](#csel_ident_fold)

---

<a id="csel_read_ident"></a>

### `csel_read_ident`

`function` | [src/css_select.c:152](../../src/css_select.c#L152)

```c
int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower)
```

Reads an identifier at s[*ip] (escapes decoded, non-ASCII kept, lowercased when lower != 0) into dst (CSS_TOK_MAX).

Returns 0, *ip untouched, when none.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |
| `ip` | `size_t *` |  |  |
| `b` | `size_t` |  |  |
| `dst` | `char *` |  |  |
| `lower` | `int` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`csel_read_ident`](#csel_read_ident) (include/css_select.h:230).

*Calls:* [`csel_ident_ch`](include.css_select.h.md#csel_ident_ch), [`csel_lower_ch`](include.css_select.h.md#csel_lower_ch), [`csel_escape_len`](#csel_escape_len), [`csel_ident_fold`](#csel_ident_fold), [`csel_unescape`](#csel_unescape)

---

<a id="between"></a>

### `between`

`function` | [src/css_select.c:384](../../src/css_select.c#L384)

```c
* between ( and ) is split on commas (not inside [] or ());
```

**Returns:** `*`

---

<a id="selector"></a>

### `selector`

`function` | [src/css_select.c:567](../../src/css_select.c#L567)

```c
* the whole selector (fail closed). A chain deeper than CSS_MAX_COMPOUNDS is * dropped. Whitespa...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `closed` | `fail` |  |  |

**Returns:** `* the whole`

*Calls:* [`csel_ident_fold`](#csel_ident_fold)

---

<a id="csel_element_feature_bits"></a>

### `csel_element_feature_bits`

`function` | [src/css_select.c:587](../../src/css_select.c#L587)

```c
unsigned long long csel_element_feature_bits(const css_element *e)
```

Ancestor filter. csel_element_feature_bits: the bits of one element's tag, id and classes (two bits per feature, hashed the way csel_ident_eq compares). csel_anc_reject: 1 when the selector REQUIRES a feature that none of the element's ancestors has (or that the element itself lacks: a class or tag of its own compound), so it cannot match and need not be evaluated; 0 when it might.

Conservative by construction: no bloom (anc_bloom_valid == 0) or no requirement answers 0, and only compounds reachable through descendant/child combinators count.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `e` | `css_element *` |  |  |

**Returns:** `unsigned long long`

> **Inherited:** Documentation from [`csel_element_feature_bits`](#csel_element_feature_bits) (include/css_select.h:193).

---

<a id="seven"></a>

### `seven`

`function` | [src/css_select.c:621](../../src/css_select.c#L621)

```c
* pay for the other seven (a css_sel is ~12.8 KiB). */ memset(sel, 0, offsetof(css_sel, parts));
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `KiB` | `a css_sel is ~12.8` |  |  |

**Returns:** `* pay for the other`

---

<a id="csel_compact_size"></a>

### `csel_compact_size`

`function` | [src/css_select.c:729](../../src/css_select.c#L729)

```c
size_t csel_compact_size(int nparts)
```

Bytes a selector with `nparts` compounds needs: the header plus the compounds it uses.

A full css_sel is ~12.8 KiB; a typical rule selector (1-3 compounds) needs a third of that, and a stylesheet holds tens of thousands of them.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `nparts` | `int` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`csel_compact_size`](#csel_compact_size) (include/css_select.h:167).

*Called by:* [`csel_compact_dup`](#csel_compact_dup)

---

<a id="csel_compact_dup"></a>

### `csel_compact_dup`

`function` | [src/css_select.c:735](../../src/css_select.c#L735)

```c
css_sel *csel_compact_dup(const css_sel *sel)
```

Heap copy of *sel holding only the compounds in use (free()d by the caller); NULL on OOM or a selector with nparts outside [1, CSS_MAX_COMPOUNDS].

The copy is read-only for matching: parts[k] for k >= nparts is not backed by memory.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `sel` | `css_sel *` |  |  |

**Returns:** `css_sel *`

> **Inherited:** Documentation from [`csel_compact_dup`](#csel_compact_dup) (include/css_select.h:172).

*Calls:* [`csel_compact_size`](#csel_compact_size)

---

<a id="csel_parse"></a>

### `csel_parse`

`function` | [src/css_select.c:744](../../src/css_select.c#L744)

```c
int csel_parse(const char *s, size_t a, size_t b, css_sel *sel)
```

Parses the complex selector s[a,b) into *sel (spec computed; order/rule left to the caller).

Returns 1 if supported, 0 to drop the selector (fail closed).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |
| `a` | `size_t` |  |  |
| `b` | `size_t` |  |  |
| `sel` | `css_sel *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`csel_parse`](#csel_parse) (include/css_select.h:176).

---

<a id="built"></a>

### `built`

`function` | [src/css_select.c:1115](../../src/css_select.c#L1115)

```c
* chains the caller built (an element without parent/prev links never matches * through that combinator — fail closed). When pseudo_kind is non-NULL and the * subject compound (rightmost, index k) matches via PSEUDO_BEFORE or * PSEUDO_AFTER, *pseudo_kind is set to that kind. */ static int complex_matches(const css_sel *sel, int k, const css_element *el, const char *target_id, int allow_pseudo_el, int *pseudo_kind)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `closed` | `an element without parent/prev links never matches * through that combinator — fail` |  |  |

**Returns:** `* chains the caller`

---

<a id="csel_needs_structure"></a>

### `csel_needs_structure`

`function` | [src/css_select.c:1173](../../src/css_select.c#L1173)

```c
int csel_needs_structure(const css_sel *sel)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `sel` | `css_sel *` |  |  |

**Returns:** `int`

*Called by:* [`cch_element_matches`](src.css_chain.c.md#cch_element_matches)

---

<a id="csel_matches"></a>

### `csel_matches`

`function` | [src/css_select.c:1196](../../src/css_select.c#L1196)

```c
int csel_matches(const css_sel *sel, const css_element *el, const char *target_id, int allow_pseudo_el, int *pseudo_kind)
```

True if *sel matches element *el against its ancestor chain. target_id (optional) is the URL fragment for :target matching; NULL -> never matches. allow_pseudo_el: 1 = CSS cascade mode (::before/::after match), 0 = DOM query mode (pseudo-elements never match real elements). pseudo_kind (optional, may be NULL): when non-NULL and the subject compound matched via PSEUDO_BEFORE or PSEUDO_AFTER, *pseudo_kind is set to that pseudo-element kind; otherwise set to -1.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `sel` | `css_sel *` |  |  |
| `el` | `css_element *` |  |  |
| `target_id` | `char *` |  |  |
| `allow_pseudo_el` | `int` |  |  |
| `pseudo_kind` | `int *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`csel_matches`](#csel_matches) (include/css_select.h:185).

---

## Macros

<a id="has_max_depth"></a>

### `HAS_MAX_DEPTH`

`macro` | [src/css_select.c:939](../../src/css_select.c#L939)

```c
#define HAS_MAX_DEPTH
```

Recursive depth cap to prevent unbounded traversal on deep DOM.

---
