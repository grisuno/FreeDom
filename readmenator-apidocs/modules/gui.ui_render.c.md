# `gui/ui_render.c`

> Source: [gui/ui_render.c:1](../../gui/ui_render.c#L1) | language `c` | coverage 37.5% | [API index](../index.md)

## Contents

- **Structs:** [`ui_window`](#ui_window)
- **Functions:** [`ui_run_text_view`](#ui_run_text_view)
- **Macros:** [`_GNU_SOURCE`](#_gnu_source), [`UI_FONT_SIZE`](#ui_font_size), [`UI_MARGIN`](#ui_margin), [`UI_BTN_W`](#ui_btn_w), [`UI_BTN_LEFT`](#ui_btn_left)

## Structs

<a id="ui_window"></a>

### `ui_window`

`struct` | [gui/ui_render.c:67](../../gui/ui_render.c#L67)

```c
typedef struct ui_window
```

---

## Functions

<a id="ui_run_text_view"></a>

### `ui_run_text_view`

`function` | [gui/ui_render.c:410](../../gui/ui_render.c#L410)

```c
ui_status ui_run_text_view(const char *title, const char *text, size_t text_len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `title` | `char *` |  |  |
| `text` | `char *` |  |  |
| `text_len` | `size_t` |  |  |

**Returns:** `ui_status`

*Called by:* [`main`](gui.freedom_view.c.md#main)

---

## Macros

<a id="_gnu_source"></a>

### `_GNU_SOURCE`

`macro` | [gui/ui_render.c:10](../../gui/ui_render.c#L10)

```c
#define _GNU_SOURCE
```

---

<a id="ui_font_size"></a>

### `UI_FONT_SIZE`

`macro` | [gui/ui_render.c:28](../../gui/ui_render.c#L28)

```c
#define UI_FONT_SIZE
```

The web's base font size AND the root css.c resolves px/rem against.

One number governs both or the two drift: at 14 every page rendered ~12% small and an absolute `font-size:40px` landed at 250% x 14 = 35px. spec/box_style.md "Metricas UA del tema".

> **Inherited:** Documentation from [`UI_FONT_SIZE`](#ui_font_size) (gui/browser_ui_internal.h:30).

---

<a id="ui_margin"></a>

### `UI_MARGIN`

`macro` | [gui/ui_render.c:29](../../gui/ui_render.c#L29)

```c
#define UI_MARGIN
```

---

<a id="ui_btn_w"></a>

### `UI_BTN_W`

`macro` | [gui/ui_render.c:31](../../gui/ui_render.c#L31)

```c
#define UI_BTN_W
```

client-side titlebar height

---

<a id="ui_btn_left"></a>

### `UI_BTN_LEFT`

`macro` | [gui/ui_render.c:32](../../gui/ui_render.c#L32)

```c
#define UI_BTN_LEFT
```

min/max/close button width

---
