# `src/render_doc.c`

> Source: [src/render_doc.c:1](../../src/render_doc.c#L1) | language `c` | coverage 50.0% | [API index](../index.md)

## Contents

- **Functions:** [`place`](#place), [`rd_build`](#rd_build), [`unset`](#unset), [`rd_free`](#rd_free), [`rd_count`](#rd_count), [`rd_at`](#rd_at), [`rd_box_count`](#rd_box_count), [`rd_box_at`](#rd_box_at), [`rd_cont_count`](#rd_cont_count), [`rd_cont_at`](#rd_cont_at), [`rd_kind_name`](#rd_kind_name), [`rd_block_heading_level`](#rd_block_heading_level), [`rd_block_tag`](#rd_block_tag), [`rd_input_label`](#rd_input_label), [`rd_input_invisible`](#rd_input_invisible), [`rd_image_label`](#rd_image_label), [`rd_image_fail_label`](#rd_image_fail_label)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_render_doc_c__rd_build(["rd_build"])
    n_src_render_doc_c__rd_free(["rd_free"])
    n_include_render_doc_h__rdp_images_warning["render_doc.rdp_images_warning"]
    n_src_url_c__url_resolve_https["url.url_resolve_https"]
    n_src_render_doc_c__rd_build --> n_src_render_doc_c__rd_free
    n_src_render_doc_c__rd_build -.-> n_include_render_doc_h__rdp_images_warning
    n_src_render_doc_c__rd_build -.-> n_src_url_c__url_resolve_https
```

## Functions

<a id="place"></a>

### `place`

`function` | [src/render_doc.c:236](../../src/render_doc.c#L236)

```c
* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in place (never resolved, never touches the network either way);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `resolved` | `never` |  |  |
| `way` | `never touches the network either` |  |  |

**Returns:** `* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in`

---

<a id="rd_build"></a>

### `rd_build`

`function` | [src/render_doc.c:268](../../src/render_doc.c#L268)

```c
rd_status rd_build(const pv_view *view, rdp_caps caps, const char *top_level_url, rd_doc **out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `view` | `pv_view *` |  |  |
| `caps` | `rdp_caps` |  |  |
| `top_level_url` | `char *` |  |  |
| `out` | `rd_doc **` |  |  |

**Returns:** `rd_status`

*Calls:* [`rdp_images_warning`](include.render_doc.h.md#rdp_images_warning), [`rd_free`](#rd_free), [`url_resolve_https`](src.url.c.md#url_resolve_https)

---

<a id="unset"></a>

### `unset`

`function` | [src/render_doc.c:675](../../src/render_doc.c#L675)

```c
* background paints as if unset (no border/box-shadow-style * "broken image" placeholder) -- it is decoration, not content * with alt text, matching real-browser behaviour. */ if (d->boxes[i].bg_image_url[0] != '\0')
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `placeholder` | `no border/box-shadow-style * "broken image"` |  |  |

**Returns:** `* background paints as if`

*Called by:* [`CSS_NTH_MAX`](include.css.h.md#css_nth_max)

---

<a id="rd_free"></a>

### `rd_free`

`function` | [src/render_doc.c:740](../../src/render_doc.c#L740)

```c
void rd_free(rd_doc *d)
```

Idempotent; safe on NULL and safe to call twice.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `d` | `rd_doc *` |  |  |

> **Inherited:** Documentation from [`rd_free`](#rd_free) (include/render_doc.h:314).

*Called by:* [`rd_build`](#rd_build)

---

<a id="rd_count"></a>

### `rd_count`

`function` | [src/render_doc.c:757](../../src/render_doc.c#L757)

```c
size_t rd_count(const rd_doc *d)
```

Read accessors.

NULL-safe.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `d` | `rd_doc *` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`rd_count`](#rd_count) (include/render_doc.h:317).

---

<a id="rd_at"></a>

### `rd_at`

`function` `const` | [src/render_doc.c:761](../../src/render_doc.c#L761)

```c
const rd_block *rd_at(const rd_doc *d, size_t i)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `d` | `rd_doc *` |  |  |
| `i` | `size_t` |  |  |

**Returns:** `rd_block *`

---

<a id="rd_box_count"></a>

### `rd_box_count`

`function` | [src/render_doc.c:766](../../src/render_doc.c#L766)

```c
size_t rd_box_count(const rd_doc *d)
```

Box tree accessors (Step D). rd_box_count is the number of box definitions (0 when caps.css is off); rd_box_at returns boxes[i] (i == a block_id) or NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `d` | `rd_doc *` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`rd_box_count`](#rd_box_count) (include/render_doc.h:322).

---

<a id="rd_box_at"></a>

### `rd_box_at`

`function` `const` | [src/render_doc.c:770](../../src/render_doc.c#L770)

```c
const pv_box_def *rd_box_at(const rd_doc *d, size_t i)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `d` | `rd_doc *` |  |  |
| `i` | `size_t` |  |  |

**Returns:** `pv_box_def *`

---

<a id="rd_cont_count"></a>

### `rd_cont_count`

`function` | [src/render_doc.c:775](../../src/render_doc.c#L775)

```c
size_t rd_cont_count(const rd_doc *d)
```

Container table accessors. rd_cont_count is the number of containers; rd_cont_at returns conts[i] (i == a run's cont_id) or NULL when out of range.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `d` | `rd_doc *` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`rd_cont_count`](#rd_cont_count) (include/render_doc.h:327).

---

<a id="rd_cont_at"></a>

### `rd_cont_at`

`function` `const` | [src/render_doc.c:779](../../src/render_doc.c#L779)

```c
const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `d` | `rd_doc *` |  |  |
| `i` | `size_t` |  |  |

**Returns:** `pv_cont_def *`

---

<a id="rd_kind_name"></a>

### `rd_kind_name`

`function` `const` | [src/render_doc.c:784](../../src/render_doc.c#L784)

```c
const char *rd_kind_name(rd_kind k)
```

Stable, short English name of a block kind for structured/agent output.

Never NULL; an unknown enum value yields "block".

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `k` | `rd_kind` |  |  |

**Returns:** `char *`

> **Inherited:** Documentation from [`rd_kind_name`](#rd_kind_name) (include/render_doc.h:332).

---

<a id="rd_block_heading_level"></a>

### `rd_block_heading_level`

`function` | [src/render_doc.c:798](../../src/render_doc.c#L798)

```c
int rd_block_heading_level(const rd_block *b)
```

Effective heading level of a block, 0 when it is not heading content.

RD_HEADING yields its heading_level clamped to 1..6; an RD_LINK carrying heading_level >= 1 (an <a> wrapping or inside an <h2>) yields that level clamped, because the link only changes colour and underline -- the UA sheet still gives its text the heading's size and margins. Anything else, or NULL, yields 0. Pure and total.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `rd_block *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`rd_block_heading_level`](#rd_block_heading_level) (include/render_doc.h:347).

---

<a id="rd_block_tag"></a>

### `rd_block_tag`

`function` `const` | [src/render_doc.c:809](../../src/render_doc.c#L809)

```c
const char *rd_block_tag(const rd_block *b)
```

Canonical HTML tag name for a block, so the presentation layer can look up its user-agent box (box_style) without re-deriving the kind->tag mapping at the call site.

RD_HEADING -> "h1".."h6" (heading_level clamped to 1..6), RD_PARAGRAPH -> "p", RD_LINK -> "a", RD_IMAGE -> "img", RD_INPUT -> "textarea"/"button"/"input" by input_type. RD_NOTICE (a user-agent banner, not an HTML element) and a NULL block yield NULL. The returned string is a static literal (not owned).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `rd_block *` |  |  |

**Returns:** `char *`

> **Inherited:** Documentation from [`rd_block_tag`](#rd_block_tag) (include/render_doc.h:340).

---

<a id="rd_input_label"></a>

### `rd_input_label`

`function` `const` | [src/render_doc.c:840](../../src/render_doc.c#L840)

```c
const char *rd_input_label(int input_type)
```

Stable, short English name of a form control type (a pv_input_type value), e.g.

"text" / "password" / "submit". Never NULL; an unknown value yields "field".

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `input_type` | `int` |  |  |

**Returns:** `char *`

> **Inherited:** Documentation from [`rd_input_label`](#rd_input_label) (include/render_doc.h:361).

---

<a id="rd_input_invisible"></a>

### `rd_input_invisible`

`function` | [src/render_doc.c:860](../../src/render_doc.c#L860)

```c
int rd_input_invisible(int input_type)
```

Nonzero iff a control of this type has no face of its own and is therefore never laid out or painted: a hidden field, or the submit proxy of a <button> whose face is its own content box.

Its data still takes part in form submission.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `input_type` | `int` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`rd_input_invisible`](#rd_input_invisible) (include/render_doc.h:366).

---

<a id="rd_image_label"></a>

### `rd_image_label`

`function` `const` | [src/render_doc.c:864](../../src/render_doc.c#L864)

```c
const char *rd_image_label(rdp_img_decision d)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `d` | `rdp_img_decision` |  |  |

**Returns:** `char *`

---

<a id="rd_image_fail_label"></a>

### `rd_image_fail_label`

`function` `const` | [src/render_doc.c:875](../../src/render_doc.c#L875)

```c
const char *rd_image_fail_label(img_fail_reason reason)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `reason` | `img_fail_reason` |  |  |

**Returns:** `char *`

---
