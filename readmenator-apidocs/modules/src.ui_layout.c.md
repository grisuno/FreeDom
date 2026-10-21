# `src/ui_layout.c`

> Source: [src/ui_layout.c:1](../../src/ui_layout.c#L1) | language `c` | coverage 50.0% | [API index](../index.md)

## Contents

- **Functions:** [`ui_wrap_text`](#ui_wrap_text), [`ui_layout_free`](#ui_layout_free), [`ui_clamp_scroll`](#ui_clamp_scroll)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_ui_layout_c__ui_wrap_text(["ui_wrap_text"])
    n_src_ui_layout_c__ui_layout_free(["ui_layout_free"])
    n_src_ui_layout_c__ui_wrap_text --> n_src_ui_layout_c__ui_layout_free
```

## Functions

<a id="ui_wrap_text"></a>

### `ui_wrap_text`

`function` | [src/ui_layout.c:27](../../src/ui_layout.c#L27)

```c
ui_status ui_wrap_text(const char *text, size_t len, size_t max_cols, ui_layout *out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `text` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `max_cols` | `size_t` |  |  |
| `out` | `ui_layout *` |  |  |

**Returns:** `ui_status`

*Calls:* [`ui_layout_free`](#ui_layout_free)

---

<a id="ui_layout_free"></a>

### `ui_layout_free`

`function` | [src/ui_layout.c:91](../../src/ui_layout.c#L91)

```c
void ui_layout_free(ui_layout *lay)
```

Idempotent; safe on a zero-initialised struct and safe to call twice.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lay` | `ui_layout *` |  |  |

> **Inherited:** Documentation from [`ui_layout_free`](#ui_layout_free) (include/ui.h:52).

*Called by:* [`ui_wrap_text`](#ui_wrap_text)

---

<a id="ui_clamp_scroll"></a>

### `ui_clamp_scroll`

`function` | [src/ui_layout.c:99](../../src/ui_layout.c#L99)

```c
size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines)
```

Clamps desired to [0, max(0, total_lines - viewport_lines)].

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `desired` | `size_t` |  |  |
| `total_lines` | `size_t` |  |  |
| `viewport_lines` | `size_t` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`ui_clamp_scroll`](#ui_clamp_scroll) (include/ui.h:55).

---
