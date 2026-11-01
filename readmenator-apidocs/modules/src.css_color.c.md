# `src/css_color.c`

> Source: [src/css_color.c:1](../../src/css_color.c#L1) | language `c` | coverage 41.2% | [API index](../index.md)

## Contents

- **Structs:** [`cc_named`](#cc_named), [`cc_cv`](#cc_cv), [`cc_cp`](#cc_cp)
- **Type Aliases:** [`v`](#v)
- **Functions:** [`span`](#span), [`cc_parse`](#cc_parse), [`strncmp`](#strncmp), [`cc_pack`](#cc_pack), [`cc_unpack`](#cc_unpack)
- **Macros:** [`CC_TOKEN_MAX`](#cc_token_max), [`CC_CHANNEL_MAX`](#cc_channel_max), [`CC_PERCENT_MAX`](#cc_percent_max), [`CC_NUMBER_MAX_DIGITS`](#cc_number_max_digits), [`CC_HSL_SCALE`](#cc_hsl_scale), [`CC_CALC_DEPTH`](#cc_calc_depth), [`CC_PI`](#cc_pi)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class cc_named
    <<struct>> cc_named
    class v
    <<type_alias>> v
    class cc_cv
    <<struct>> cc_cv
    class cc_cp
    <<struct>> cc_cp
```

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_css_color_c__cc_parse(["cc_parse"])
    n_src_css_color_c__strncmp(["strncmp"])
    n_gui_browser_ui_c__strcmp["browser_ui.strcmp"]
    n_src_css_color_c__cc_parse --> n_src_css_color_c__strncmp
    n_src_css_color_c__cc_parse -.-> n_gui_browser_ui_c__strcmp
    n_src_css_color_c__strncmp -.-> n_gui_browser_ui_c__strcmp
```

## Structs

<a id="cc_named"></a>

### `cc_named`

`struct` | [src/css_color.c:34](../../src/css_color.c#L34)

```c
typedef struct cc_named
```

---

<a id="cc_cv"></a>

### `cc_cv`

`struct` | [src/css_color.c:223](../../src/css_color.c#L223)

```c
typedef struct cc_cv { double v; int pct; } cc_cv;
```

---

<a id="cc_cp"></a>

### `cc_cp`

`struct` `const` | [src/css_color.c:224](../../src/css_color.c#L224)

```c
typedef struct cc_cp { const char *p, *e; } cc_cp;
```

---

## Type Aliases

<a id="v"></a>

### `v`

`type_alias` | [src/css_color.c:222](../../src/css_color.c#L222)

```c
typedef struct cc_cv { double v;
```

-- calc() inside a colour component (CSS Values 4 section 10) ---------------- A channel may be a calc() over <number>s and <percentage>s (GitHub writes `hsl(0deg, 0%, calc(var(--switch) * 100%))`, Discord `hsl(235, calc(1*86.1%), 71.8%)`).

The expression is folded to one literal before the component parser sees it, so the range checks stay in exactly one place. Depth-bounded recursive descent over a * bounded span; a percentage times a percentage, or a sum mixing the two, fails. define CC_CALC_DEPTH 8

---

## Functions

<a id="span"></a>

### `span`

`function` | [src/css_color.c:431](../../src/css_color.c#L431)

```c
* span (when a slash is present) into ab/ae, and returns the component count, * or -1. Bounded: ...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `present` | `when a slash is` |  |  |

**Returns:** `*`

---

<a id="cc_parse"></a>

### `cc_parse`

`function` | [src/css_color.c:697](../../src/css_color.c#L697)

```c
cc_status cc_parse(const char *token, cc_rgb *out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `token` | `char *` |  |  |
| `out` | `cc_rgb *` |  |  |

**Returns:** `cc_status`

*Calls:* [`strcmp`](gui.browser_ui.c.md#strcmp), [`strncmp`](#strncmp)

*Called by:* [`cv_parse_color`](src.css_values.c.md#cv_parse_color), [`PV_COLOR_TOKEN_MAX`](src.page_view.c.md#pv_color_token_max)

---

<a id="strncmp"></a>

### `strncmp`

`function` | [src/css_color.c:712](../../src/css_color.c#L712)

```c
strncmp(buf, "oklab(", 6) == 0 || strncmp(buf, "oklch(", 6) == 0)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `oklab` |  |  |  |
| `6)` |  | `= 0 \|\| strncmp(buf, "oklch(", 6) == 0)` |  |

*Calls:* [`strcmp`](gui.browser_ui.c.md#strcmp)

*Called by:* [`arrives`](gui.browser_ui.c.md#arrives), [`only`](gui.browser_ui.c.md#only), [`blur`](src.css.c.md#blur), [`cb_clip_inset`](src.css_box.c.md#cb_clip_inset), [`cc_parse`](#cc_parse), [`cnt_is_marker`](src.css_counter.c.md#cnt_is_marker), [`cnt_parse_decls`](src.css_counter.c.md#cnt_parse_decls), [`cmq_container_surely`](src.css_mq.c.md#cmq_container_surely), [`dl_should_download`](src.download.c.md#dl_should_download), [`gets`](src.freedom.c.md#gets), [`main`](src.freedom.c.md#main), [`parent`](src.freedom.c.md#parent) and 6 more

---

<a id="cc_pack"></a>

### `cc_pack`

`function` | [src/css_color.c:737](../../src/css_color.c#L737)

```c
int cc_pack(cc_rgb c)
```

Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport and for the pipeline's "no color" sentinel of -1).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `cc_rgb` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`cc_pack`](#cc_pack) (include/css_color.h:49).

---

<a id="cc_unpack"></a>

### `cc_unpack`

`function` | [src/css_color.c:741](../../src/css_color.c#L741)

```c
cc_rgb cc_unpack(int packed)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `packed` | `int` |  |  |

**Returns:** `cc_rgb`

*Called by:* [`rgb_from_packed`](gui.bui_theme.c.md#rgb_from_packed)

---

## Macros

<a id="cc_token_max"></a>

### `CC_TOKEN_MAX`

`macro` | [src/css_color.c:20](../../src/css_color.c#L20)

```c
#define CC_TOKEN_MAX
```

Largest CSS color token accepted.

The longest named color ("lightgoldenrodyellow") is 20 bytes; functional rgba() with percentages fits well under this. A longer token is not a color and fails closed.

---

<a id="cc_channel_max"></a>

### `CC_CHANNEL_MAX`

`macro` | [src/css_color.c:23](../../src/css_color.c#L23)

```c
#define CC_CHANNEL_MAX
```

Channel maxima for the rgb() functional form.

---

<a id="cc_percent_max"></a>

### `CC_PERCENT_MAX`

`macro` | [src/css_color.c:24](../../src/css_color.c#L24)

```c
#define CC_PERCENT_MAX
```

---

<a id="cc_number_max_digits"></a>

### `CC_NUMBER_MAX_DIGITS`

`macro` | [src/css_color.c:29](../../src/css_color.c#L29)

```c
#define CC_NUMBER_MAX_DIGITS
```

Digits accepted on either side of the decimal point in one component.

A real value has a handful; the cap is what stops a hostile stylesheet from handing the scanner an unbounded digit run (anti-DoS, fail closed). A preprocessor emitting `91.862745098%` uses 9 fractional digits, so the bound is set well clear of it.

---

<a id="cc_hsl_scale"></a>

### `CC_HSL_SCALE`

`macro` | [src/css_color.c:32](../../src/css_color.c#L32)

```c
#define CC_HSL_SCALE
```

Fixed-point scale for hsl() saturation/lightness: hundredths of a percent, so 100% is CC_HSL_SCALE.

See parse_hsl_comp.

---

<a id="cc_calc_depth"></a>

### `CC_CALC_DEPTH`

`macro` | [src/css_color.c:221](../../src/css_color.c#L221)

```c
#define CC_CALC_DEPTH
```

--- calc() inside a colour component (CSS Values 4 section 10) ----------------
A channel may be a calc() over <number>s and <percentage>s (GitHub writes
`hsl(0deg, 0%, calc(var(--switch) * 100%))`, Discord `hsl(235, calc(1*86.1%), 71.8%)`).
The expression is folded to one literal before the component parser sees it, so
the range checks stay in exactly one place. Depth-bounded recursive descent over a
bounded span; a percentage times a percentage, or a sum mixing the two, fails.

---

<a id="cc_pi"></a>

### `CC_PI`

`macro` | [src/css_color.c:577](../../src/css_color.c#L577)

```c
#define CC_PI
```

---
