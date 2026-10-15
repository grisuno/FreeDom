# `include/css_gradient.h`

> Source: [include/css_gradient.h:1](../../include/css_gradient.h#L1) | language `h` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`cg_expand_bg_image`](#cg_expand_bg_image), [`cg_expand_background`](#cg_expand_background)

## Functions

<a id="cg_expand_bg_image"></a>

### `cg_expand_bg_image`

`function` | [include/css_gradient.h:11](../../include/css_gradient.h#L11)

```c
int cg_expand_bg_image(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `val` | `char *` |  |  |
| `dst` | `css_decl *` |  |  |
| `cap` | `int` |  |  |
| `CSS_URL_MAX` | `char (*urltab)[ ]` |  |  |
| `nurl` | `size_t *` |  |  |
| `urlcap` | `size_t` |  |  |

**Returns:** `int`

*Called by:* [`downstream`](src.css_gradient.c.md#downstream)

---

<a id="cg_expand_background"></a>

### `cg_expand_background`

`function` | [include/css_gradient.h:13](../../include/css_gradient.h#L13)

```c
int cg_expand_background(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `val` | `char *` |  |  |
| `dst` | `css_decl *` |  |  |
| `cap` | `int` |  |  |
| `CSS_URL_MAX` | `char (*urltab)[ ]` |  |  |
| `nurl` | `size_t *` |  |  |
| `urlcap` | `size_t` |  |  |

**Returns:** `int`

---
