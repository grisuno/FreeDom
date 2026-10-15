# `gui/freedom_view.c`

> Source: [gui/freedom_view.c:1](../../gui/freedom_view.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`main`](#main)
- **Macros:** [`_POSIX_C_SOURCE`](#_posix_c_source)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_gui_freedom_view_c__main(["main"])
    n_gui_ui_render_c__ui_run_text_view["ui_render.ui_run_text_view"]
    n_include_html_parse_h__hp_document_free["html_parse.hp_document_free"]
    n_include_html_parse_h__hp_extract_text["html_parse.hp_extract_text"]
    n_include_html_parse_h__hp_free["html_parse.hp_free"]
    n_include_html_parse_h__hp_get_title["html_parse.hp_get_title"]
    n_src_html_parse_c__hp_parse["html_parse.hp_parse"]
    n_gui_freedom_view_c__main -.-> n_gui_ui_render_c__ui_run_text_view
    n_gui_freedom_view_c__main -.-> n_include_html_parse_h__hp_document_free
    n_gui_freedom_view_c__main -.-> n_include_html_parse_h__hp_extract_text
    n_gui_freedom_view_c__main -.-> n_include_html_parse_h__hp_free
    n_gui_freedom_view_c__main -.-> n_include_html_parse_h__hp_get_title
    n_gui_freedom_view_c__main -.-> n_src_html_parse_c__hp_parse
```

## Functions

<a id="main"></a>

### `main`

`function` | [gui/freedom_view.c:37](../../gui/freedom_view.c#L37)

```c
int main(int argc, char **argv)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int` |  |  |
| `argv` | `char **` |  |  |

**Returns:** `int`

*Calls:* [`ui_run_text_view`](gui.ui_render.c.md#ui_run_text_view), [`hp_document_free`](include.html_parse.h.md#hp_document_free), [`hp_extract_text`](include.html_parse.h.md#hp_extract_text), [`hp_free`](include.html_parse.h.md#hp_free), [`hp_get_title`](include.html_parse.h.md#hp_get_title), [`hp_parse`](src.html_parse.c.md#hp_parse)

---

## Macros

<a id="_posix_c_source"></a>

### `_POSIX_C_SOURCE`

`macro` | [gui/freedom_view.c:10](../../gui/freedom_view.c#L10)

```c
#define _POSIX_C_SOURCE
```

---
