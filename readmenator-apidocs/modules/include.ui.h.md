# `include/ui.h`

> Source: [include/ui.h:1](../../include/ui.h#L1) | language `h` | coverage 35.0% | [API index](../index.md)

## Contents

- **Structs:** [`ui_line`](#ui_line), [`ui_layout`](#ui_layout), [`rd_doc`](#rd_doc), [`jg_table`](#jg_table), [`tab`](#tab), [`fh_host`](#fh_host)
- **Enums:** [`ui_status`](#ui_status)
- **Type Aliases:** [`offset`](#offset)
- **Functions:** [`space`](#space), [`ui_layout_free`](#ui_layout_free), [`ui_clamp_scroll`](#ui_clamp_scroll), [`shortcut`](#shortcut), [`available`](#available), [`out`](#out), [`placeholders`](#placeholders), [`disk`](#disk), [`images`](#images), [`ui_render_viewport_w`](#ui_render_viewport_w), [`ui_persisted_prefs`](#ui_persisted_prefs)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class ui_status
    <<enum>> ui_status
    class offset
    <<type_alias>> offset
    class ui_line
    <<struct>> ui_line
    class ui_layout
    <<struct>> ui_layout
    class rd_doc
    <<struct>> rd_doc
    class jg_table
    <<struct>> jg_table
    class tab
    <<struct>> tab
    class fh_host
    <<struct>> fh_host
```

## Structs

<a id="ui_line"></a>

### `ui_line`

`struct` | [include/ui.h:30](../../include/ui.h#L30)

```c
typedef struct ui_line
```

A laid-out line is a contiguous slice [offset, offset+len) of the source text (no copy): render with text + offset over len bytes.

---

<a id="ui_layout"></a>

### `ui_layout`

`struct` | [include/ui.h:35](../../include/ui.h#L35)

```c
typedef struct ui_layout
```

---

<a id="rd_doc"></a>

### `rd_doc`

`struct` | [include/ui.h:74](../../include/ui.h#L74)

```c
struct rd_doc;
```

---

<a id="jg_table"></a>

### `jg_table`

`struct` | [include/ui.h:100](../../include/ui.h#L100)

```c
struct jg_table;
```

---

<a id="tab"></a>

### `tab`

`struct` | [include/ui.h:110](../../include/ui.h#L110)

```c
struct tab;
```

---

<a id="fh_host"></a>

### `fh_host`

`struct` | [include/ui.h:130](../../include/ui.h#L130)

```c
struct fh_host;
```

ui_render_png_images, plus the live <iframe>s of a trusted page: [`frames`](src.tab.c.md#frames) (may be NULL) is the frame host whose documents are painted into the frame boxes, exactly as the window does.

---

## Enums

<a id="ui_status"></a>

### `ui_status`

`enum` | [include/ui.h:20](../../include/ui.h#L20)

```c
typedef enum ui_status
```

---

## Type Aliases

<a id="offset"></a>

### `offset`

`type_alias` | [include/ui.h:30](../../include/ui.h#L30)

```c
typedef struct ui_line { size_t offset;
```

A laid-out line is a contiguous slice [offset, offset+len) of the source text (no copy): render with text + offset over len bytes.

---

## Functions

<a id="space"></a>

### `space`

`function` | [include/ui.h:44](../../include/ui.h#L44)

```c
* Breaks at the last fitting space (the break space is consumed), hard-breaks * words longer than max_cols, and treats '\n' as a forced break. max_cols == 0 * is treated as 1. len == 0 yields zero lin
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `consumed` | `the break space is` |  |  |

**Returns:** `* Breaks at the last fitting`

---

<a id="ui_layout_free"></a>

### `ui_layout_free`

`function` | [include/ui.h:52](../../include/ui.h#L52)

```c
void ui_layout_free(ui_layout *lay);
```

Idempotent; safe on a zero-initialised struct and safe to call twice.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lay` | `ui_layout *` |  |  |

---

<a id="ui_clamp_scroll"></a>

### `ui_clamp_scroll`

`function` | [include/ui.h:55](../../include/ui.h#L55)

```c
size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines);
```

Clamps desired to [0, max(0, total_lines - viewport_lines)].

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `desired` | `size_t` |  |  |
| `total_lines` | `size_t` |  |  |
| `viewport_lines` | `size_t` |  |  |

**Returns:** `size_t`

---

<a id="shortcut"></a>

### `shortcut`

`function` | [include/ui.h:71](../../include/ui.h#L71)

```c
* from a keyboard shortcut (Ctrl+Shift+E only relaxes a weak-but-valid certificate). */ void ui_set_operator_insecure(int on);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `certificate` | `Ctrl+Shift+E only relaxes a weak-but-valid` |  |  |

**Returns:** `* from a keyboard`

---

<a id="available"></a>

### `available`

`function` | [include/ui.h:91](../../include/ui.h#L91)

```c
* cheapest artifact to inspect a render where no display is available (CI, an AI * agent): export, then read the PNG directly (no PDF rasterise step). The image * height is bounded (a hostile page can
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `agent` | `an AI *` |  |  |

**Returns:** `export, then read the PNG directly (no PDF rasterise step). The image * height is bounded (a hostile page can`

---

<a id="out"></a>

### `out`

`function` | [include/ui.h:103](../../include/ui.h#L103)

```c
* ui_render_png does and fills *out (jg_init'ed by the caller) with one rect per * element in document coordinates, plus a FC_PNG_PAGE_W x FC_HEADLESS_VIEW_H * viewport at scroll 0. The caller hands i
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `caller` | `jg_init'ed by the` |  |  |

**Returns:** `* ui_render_png does and fills *`

---

<a id="placeholders"></a>

### `placeholders`

`function` | [include/ui.h:113](../../include/ui.h#L113)

```c
* above always draw image placeholders (no worker to decode hostile bytes);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bytes` | `no worker to decode hostile` |  |  |

**Returns:** `* above always draw image`

---

<a id="disk"></a>

### `disk`

`function` | [include/ui.h:118](../../include/ui.h#L118)

```c
* images are read from disk (confined to the document directory by render_doc). * top_url is the page origin (https or file://);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `render_doc` | `confined to the document directory by` |  |  |

**Returns:** `* images are read from`

---

<a id="images"></a>

### `images`

`function` | [include/ui.h:120](../../include/ui.h#L120)

```c
* fetcher loads no images (placeholders, as before). Any image that fails falls back * to its placeholder, byte-identical to the on-screen window path. The fetcher type * matches tab_fetch_fn (include
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `before` | `as` |  |  |

**Returns:** `* fetcher loads no`

---

<a id="ui_render_viewport_w"></a>

### `ui_render_viewport_w`

`function` | [include/ui.h:156](../../include/ui.h#L156)

```c
int ui_render_viewport_w(void);
```

The fixed canvas width (px) every headless render (ui_render_png/pdf, ui_dump_layout) lays out at.

The headless driver feeds it to tab_set_viewport_w so @media width queries match the width the page is actually painted at.

**Returns:** `int`

---

<a id="ui_persisted_prefs"></a>

### `ui_persisted_prefs`

`function` | [include/ui.h:161](../../include/ui.h#L161)

```c
int ui_persisted_prefs(prefs_state *out);
```

The GUI's persisted choices (JS mode, images/CSS toggles, reader) from the encrypted profile, so `--as-gui` shows what the window shows.

Fills safe defaults and returns -1 when the profile is absent or unreadable. Never writes prefs.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `out` | `prefs_state *` |  |  |

**Returns:** `int`

---
