# `include/css_decl.h`

> Source: [include/css_decl.h:1](../../include/css_decl.h#L1) | language `h` | coverage 25.0% | [API index](../index.md)

Bound for the ::before/::after content string pool (and the grid-template

## Contents

- **Structs:** [`css_decl`](#css_decl)
- **Type Aliases:** [`prop`](#prop)
- **Functions:** [`order`](#order), [`contiguous`](#contiguous)
- **Macros:** [`CSS_MAX_BG_URLS`](#css_max_bg_urls), [`CSS_MAX_CONTENT_URLS`](#css_max_content_urls), [`CSS_MAX_KEYFRAMES`](#css_max_keyframes), [`CSS_MAX_KEYFRAME_STOPS`](#css_max_keyframe_stops), [`CSS_MAX_KEYFRAME_DECLS`](#css_max_keyframe_decls), [`CSS_INLINE_BG_URLS`](#css_inline_bg_urls), [`CSS_WIDE_PROBE_DECLS`](#css_wide_probe_decls)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class prop
    <<type_alias>> prop
    class css_decl
    <<struct>> css_decl
```

## Structs

<a id="css_decl"></a>

### `css_decl`

`struct` | [include/css_decl.h:187](../../include/css_decl.h#L187)

```c
typedef struct css_decl
```

---

## Type Aliases

<a id="prop"></a>

### `prop`

`type_alias` | [include/css_decl.h:186](../../include/css_decl.h#L186)

```c
typedef struct css_decl { int prop;
```

---

## Functions

<a id="order"></a>

### `order`

`function` | [include/css_decl.h:44](../../include/css_decl.h#L44)

```c
* The four margin slots are contiguous in CSS shorthand order (top,right,bottom, * left);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `left` |  |  |  |

**Returns:** `* The four margin slots are contiguous in CSS shorthand`

---

<a id="contiguous"></a>

### `contiguous`

`function` | [include/css_decl.h:59](../../include/css_decl.h#L59)

```c
* contiguous (dx,dy,color) so expand_shadow writes them as a group. */ P_FONTFAMILY, P_TEXTTRANSFORM, P_LETTERSPACING, P_WORDSPACING, P_SHADOW_DX, P_SHADOW_DY, P_SHADOW_COLOR, P_OPACITY, P_VALIGN, P_T
```

**Returns:** `*`

---

## Macros

<a id="css_max_bg_urls"></a>

### `CSS_MAX_BG_URLS`

`macro` | [include/css_decl.h:11](../../include/css_decl.h#L11)

```c
#define CSS_MAX_BG_URLS
```

---

<a id="css_max_content_urls"></a>

### `CSS_MAX_CONTENT_URLS`

`macro` | [include/css_decl.h:18](../../include/css_decl.h#L18)

```c
#define CSS_MAX_CONTENT_URLS
```

Bound for the ::before/::after content string pool (and the grid-template rows that share it).

Same budget as background URLs: an icon font ships hundreds of one-glyph `content` rules (a real page carried 400+), and past the cap every later rule loses its string in silence. Heap sheet, freed with it: 256 KiB transient per page parse, same as the bg pool.

---

<a id="css_max_keyframes"></a>

### `CSS_MAX_KEYFRAMES`

`macro` | [include/css_decl.h:20](../../include/css_decl.h#L20)

```c
#define CSS_MAX_KEYFRAMES
```

---

<a id="css_max_keyframe_stops"></a>

### `CSS_MAX_KEYFRAME_STOPS`

`macro` | [include/css_decl.h:21](../../include/css_decl.h#L21)

```c
#define CSS_MAX_KEYFRAME_STOPS
```

---

<a id="css_max_keyframe_decls"></a>

### `CSS_MAX_KEYFRAME_DECLS`

`macro` | [include/css_decl.h:22](../../include/css_decl.h#L22)

```c
#define CSS_MAX_KEYFRAME_DECLS
```

---

<a id="css_inline_bg_urls"></a>

### `CSS_INLINE_BG_URLS`

`macro` | [include/css_decl.h:23](../../include/css_decl.h#L23)

```c
#define CSS_INLINE_BG_URLS
```

---

<a id="css_wide_probe_decls"></a>

### `CSS_WIDE_PROBE_DECLS`

`macro` | [include/css_decl.h:29](../../include/css_decl.h#L29)

```c
#define CSS_WIDE_PROBE_DECLS
```

Scratch size for the CSS-wide-keyword probe (wide_claim).

Bounds the widest shorthand expansion in the dispatch: the four-side length shorthands emit a px and a percentage slot per side (8), grid-template-columns emits one slot per track plus the count (9), and matrix() emits seven.

---
