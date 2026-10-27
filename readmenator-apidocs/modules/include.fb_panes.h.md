# `include/fb_panes.h`

> Source: [include/fb_panes.h:1](../../include/fb_panes.h#L1) | language `h` | coverage 75.0% | [API index](../index.md)

## Contents

- **Enums:** [`fbp_tab`](#fbp_tab)
- **Functions:** [`fbp_tab_label`](#fbp_tab_label), [`fbp_tab_from_name`](#fbp_tab_from_name), [`fbp_tab_wrap`](#fbp_tab_wrap), [`fbp_tab_span`](#fbp_tab_span), [`fbp_tab_at`](#fbp_tab_at), [`fbp_is_pane`](#fbp_is_pane), [`fbp_js_quote`](#fbp_js_quote), [`fbp_expr`](#fbp_expr)
- **Macros:** [`FBP_SELECTOR_MAX`](#fbp_selector_max), [`FBP_EXPR_MAX`](#fbp_expr_max)

## Enums

<a id="fbp_tab"></a>

### `fbp_tab`

`enum` | [include/fb_panes.h:17](../../include/fb_panes.h#L17)

```c
typedef enum fbp_tab
```

---

## Functions

<a id="fbp_tab_label"></a>

### `fbp_tab_label`

`function` `const` | [include/fb_panes.h:34](../../include/fb_panes.h#L34)

```c
const char *fbp_tab_label(int tab);
```

Label of a tab; an out-of-range id is the console.

Never NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `tab` | `int` |  |  |

**Returns:** `char *`

---

<a id="fbp_tab_from_name"></a>

### `fbp_tab_from_name`

`function` | [include/fb_panes.h:37](../../include/fb_panes.h#L37)

```c
int fbp_tab_from_name(const char *name);
```

Tab named [`name`](src.text_shape.c.md#name) (case-insensitive), or -1 when unknown / NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char *` |  |  |

**Returns:** `int`

*Called by:* [`main`](src.freedom.c.md#main)

---

<a id="fbp_tab_wrap"></a>

### `fbp_tab_wrap`

`function` | [include/fb_panes.h:40](../../include/fb_panes.h#L40)

```c
int fbp_tab_wrap(int tab, int dir);
```

The tab [`dir`](include.profile.h.md#dir) steps away (cyclic); an invalid `tab` counts as the console.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `tab` | `int` |  |  |
| `dir` | `int` |  |  |

**Returns:** `int`

---

<a id="fbp_tab_span"></a>

### `fbp_tab_span`

`function` | [include/fb_panes.h:43](../../include/fb_panes.h#L43)

```c
void fbp_tab_span(int tab, double cell_w, double pad_cells, double *x, double *w);
```

x-extent of a tab in the bar: each is (letters + 2 * pad_cells) cells wide, contiguous.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `tab` | `int` |  |  |
| `cell_w` | `double` |  |  |
| `pad_cells` | `double` |  |  |
| `x` | `double *` |  |  |
| `w` | `double *` |  |  |

---

<a id="fbp_tab_at"></a>

### `fbp_tab_at`

`function` | [include/fb_panes.h:46](../../include/fb_panes.h#L46)

```c
int fbp_tab_at(double x, double cell_w, double pad_cells);
```

The tab under pointer x, or -1 outside the bar.

Exact inverse of fbp_tab_span.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `double` |  |  |
| `cell_w` | `double` |  |  |
| `pad_cells` | `double` |  |  |

**Returns:** `int`

---

<a id="fbp_is_pane"></a>

### `fbp_is_pane`

`function` | [include/fb_panes.h:49](../../include/fb_panes.h#L49)

```c
int fbp_is_pane(int tab);
```

Whether the tab's editor argument is meaningful (console: JS; others: selector/index/filter).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `tab` | `int` |  |  |

**Returns:** `int`

*Called by:* [`main`](src.freedom.c.md#main)

---

<a id="fbp_js_quote"></a>

### `fbp_js_quote`

`function` | [include/fb_panes.h:53](../../include/fb_panes.h#L53)

```c
size_t fbp_js_quote(const char *s, size_t n, char *out, size_t cap);
```

JS string literal for s[0,n) (double-quoted).

Returns its length, or 0 on failure (n too long, embedded NUL, cap too small).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |
| `n` | `size_t` |  |  |
| `out` | `char *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

*Called by:* [`fbc_names_expr`](src.fb_cmdline.c.md#fbc_names_expr)

---

<a id="fbp_expr"></a>

### `fbp_expr`

`function` | [include/fb_panes.h:57](../../include/fb_panes.h#L57)

```c
size_t fbp_expr(int tab, const char *sel, size_t n, char *out, size_t cap);
```

The expression that fills `tab`'s panel for argument sel[0,n); NUL-terminated in out.

Returns its length, or 0 for the console, a hostile/oversized argument or a small cap.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `tab` | `int` |  |  |
| `sel` | `char *` |  |  |
| `n` | `size_t` |  |  |
| `out` | `char *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

*Called by:* [`main`](src.freedom.c.md#main)

---

## Macros

<a id="fbp_selector_max"></a>

### `FBP_SELECTOR_MAX`

`macro` | [include/fb_panes.h:30](../../include/fb_panes.h#L30)

```c
#define FBP_SELECTOR_MAX
```

---

<a id="fbp_expr_max"></a>

### `FBP_EXPR_MAX`

`macro` | [include/fb_panes.h:31](../../include/fb_panes.h#L31)

```c
#define FBP_EXPR_MAX
```

bytes of the user's argument (selector / index / filter)

---
