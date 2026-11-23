# `include/chrome_layout.h`

> Source: [include/chrome_layout.h:1](../../include/chrome_layout.h#L1) | language `h` | coverage 53.8% | [API index](../index.md)

## Contents

- **Structs:** [`chl_rect`](#chl_rect), [`chl_layout`](#chl_layout), [`chl_findbar`](#chl_findbar)
- **Enums:** [`chl_status`](#chl_status), [`chl_part`](#chl_part), [`chl_find_part`](#chl_find_part), [`chl_identity`](#chl_identity)
- **Type Aliases:** [`h`](#h), [`width`](#width), [`close`](#close)
- **Functions:** [`chl_tab_rect`](#chl_tab_rect), [`chl_tab_close_rect`](#chl_tab_close_rect), [`chl_rect_has`](#chl_rect_has), [`chl_tab_drop_index`](#chl_tab_drop_index), [`chl_move_index`](#chl_move_index), [`chl_tab_for_digit`](#chl_tab_for_digit), [`chl_tab_fallback_title`](#chl_tab_fallback_title), [`chl_identity_label`](#chl_identity_label)
- **Macros:** [`CHL_PAD`](#chl_pad), [`CHL_TAB_TOP_GAP`](#chl_tab_top_gap), [`CHL_TAB_MIN_W`](#chl_tab_min_w), [`CHL_TAB_MAX_W`](#chl_tab_max_w), [`CHL_TAB_GAP`](#chl_tab_gap), [`CHL_TAB_CLOSE`](#chl_tab_close), [`CHL_TAB_CLOSE_MIN_W`](#chl_tab_close_min_w), [`CHL_NEWTAB_W`](#chl_newtab_w), [`CHL_WIN_BTN_W`](#chl_win_btn_w), [`CHL_DRAG_MIN`](#chl_drag_min), [`CHL_BTN`](#chl_btn), [`CHL_BTN_GAP`](#chl_btn_gap), [`CHL_ID_W`](#chl_id_w), [`CHL_STAR_W`](#chl_star_w), [`CHL_STAR_MIN_URL`](#chl_star_min_url), [`CHL_MORE_W`](#chl_more_w), [`CHL_DRAG_THRESHOLD`](#chl_drag_threshold), [`CHL_FIND_FIELD_W`](#chl_find_field_w), [`CHL_FIND_BTN`](#chl_find_btn), [`CHL_FIND_COUNT_W`](#chl_find_count_w)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class chl_status
    <<enum>> chl_status
    class h
    <<type_alias>> h
    class chl_rect
    <<struct>> chl_rect
    class chl_part
    <<enum>> chl_part
    class width
    <<type_alias>> width
    class chl_layout
    <<struct>> chl_layout
    class chl_find_part
    <<enum>> chl_find_part
    class close
    <<type_alias>> close
    class chl_findbar
    <<struct>> chl_findbar
    class chl_identity
    <<enum>> chl_identity
```

## Structs

<a id="chl_rect"></a>

### `chl_rect`

`struct` | [include/chrome_layout.h:40](../../include/chrome_layout.h#L40)

```c
typedef struct chl_rect { double x, y, w, h; } chl_rect;
```

---

<a id="chl_layout"></a>

### `chl_layout`

`struct` | [include/chrome_layout.h:63](../../include/chrome_layout.h#L63)

```c
typedef struct chl_layout
```

---

<a id="chl_findbar"></a>

### `chl_findbar`

`struct` | [include/chrome_layout.h:130](../../include/chrome_layout.h#L130)

```c
typedef struct chl_findbar
```

---

## Enums

<a id="chl_status"></a>

### `chl_status`

`enum` | [include/chrome_layout.h:38](../../include/chrome_layout.h#L38)

```c
typedef enum chl_status { CHL_OK = 0, CHL_EINVAL = -1 } chl_status;
```

---

<a id="chl_part"></a>

### `chl_part`

`enum` | [include/chrome_layout.h:42](../../include/chrome_layout.h#L42)

```c
typedef enum chl_part
```

---

<a id="chl_find_part"></a>

### `chl_find_part`

`enum` | [include/chrome_layout.h:121](../../include/chrome_layout.h#L121)

```c
typedef enum chl_find_part
```

---

<a id="chl_identity"></a>

### `chl_identity`

`enum` | [include/chrome_layout.h:143](../../include/chrome_layout.h#L143)

```c
typedef enum chl_identity
```

---

## Type Aliases

<a id="h"></a>

### `h`

`type_alias` | [include/chrome_layout.h:39](../../include/chrome_layout.h#L39)

```c
typedef struct chl_rect { double x, y, w, h;
```

---

<a id="width"></a>

### `width`

`type_alias` | [include/chrome_layout.h:62](../../include/chrome_layout.h#L62)

```c
typedef struct chl_layout { double width;
```

---

<a id="close"></a>

### `close`

`type_alias` | [include/chrome_layout.h:129](../../include/chrome_layout.h#L129)

```c
typedef struct chl_findbar { chl_rect bar, field, prev, next, count, close;
```

---

## Functions

<a id="chl_tab_rect"></a>

### `chl_tab_rect`

`function` | [include/chrome_layout.h:87](../../include/chrome_layout.h#L87)

```c
int chl_tab_rect(const chl_layout *l, int i, chl_rect *r);
```

Tab i's rectangle / its close button.

1 if it exists (visible), else 0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `l` | `chl_layout *` |  |  |
| `i` | `int` |  |  |
| `r` | `chl_rect *` |  |  |

**Returns:** `int`

*Called by:* [`LLVMFuzzerTestOneInput`](fuzz.fuzz_chrome_layout.c.md#llvmfuzzertestoneinput)

---

<a id="chl_tab_close_rect"></a>

### `chl_tab_close_rect`

`function` | [include/chrome_layout.h:88](../../include/chrome_layout.h#L88)

```c
int chl_tab_close_rect(const chl_layout *l, int i, chl_rect *r);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `l` | `chl_layout *` |  |  |
| `i` | `int` |  |  |
| `r` | `chl_rect *` |  |  |

**Returns:** `int`

---

<a id="chl_rect_has"></a>

### `chl_rect_has`

`function` | [include/chrome_layout.h:91](../../include/chrome_layout.h#L91)

```c
int chl_rect_has(chl_rect r, double x, double y);
```

1 if (x, y) lies inside r (half-open on the right and bottom).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `r` | `chl_rect` |  |  |
| `x` | `double` |  |  |
| `y` | `double` |  |  |

**Returns:** `int`

*Called by:* [`LLVMFuzzerTestOneInput`](fuzz.fuzz_chrome_layout.c.md#llvmfuzzertestoneinput)

---

<a id="chl_tab_drop_index"></a>

### `chl_tab_drop_index`

`function` | [include/chrome_layout.h:99](../../include/chrome_layout.h#L99)

```c
int chl_tab_drop_index(const chl_layout *l, double x);
```

Absolute index of the visible tab slot under x (clamped to the visible tabs): where a dragged tab dropped at x lands. -1 if l is NULL or no tab is visible.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `l` | `chl_layout *` |  |  |
| `x` | `double` |  |  |

**Returns:** `int`

*Called by:* [`LLVMFuzzerTestOneInput`](fuzz.fuzz_chrome_layout.c.md#llvmfuzzertestoneinput)

---

<a id="chl_move_index"></a>

### `chl_move_index`

`function` | [include/chrome_layout.h:103](../../include/chrome_layout.h#L103)

```c
int chl_move_index(int i, int from, int to);
```

Where element i ends up after the element at [`from`](include.smooth_scroll.h.md#from) moves to [`to`](include.render_doc.h.md#rd_block-to) (the others shift to close the gap and open the slot).

The single remapping for every index the GUI keeps.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `i` | `int` |  |  |
| `from` | `int` |  |  |
| `to` | `int` |  |  |

**Returns:** `int`

*Called by:* [`LLVMFuzzerTestOneInput`](fuzz.fuzz_chrome_layout.c.md#llvmfuzzertestoneinput)

---

<a id="chl_tab_for_digit"></a>

### `chl_tab_for_digit`

`function` | [include/chrome_layout.h:106](../../include/chrome_layout.h#L106)

```c
int chl_tab_for_digit(int digit, int tab_count);
```

Ctrl+<digit>: 1..8 select that tab, 9 the last one (Firefox). -1 when there is none.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `digit` | `int` |  |  |
| `tab_count` | `int` |  |  |

**Returns:** `int`

---

<a id="chl_tab_fallback_title"></a>

### `chl_tab_fallback_title`

`function` | [include/chrome_layout.h:111](../../include/chrome_layout.h#L111)

```c
void chl_tab_fallback_title(const char *url, char *out, size_t cap);
```

A tab label for a page without <title> (Firefox): a file's name for file: URLs and local paths, otherwise the URL without its "scheme://".

Writes "" for NULL/empty. Truncates on a UTF-8 boundary; out is always NUL-terminated when cap > 0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `url` | `char *` |  |  |
| `out` | `char *` |  |  |
| `cap` | `size_t` |  |  |

*Called by:* [`LLVMFuzzerTestOneInput`](fuzz.fuzz_chrome_layout.c.md#llvmfuzzertestoneinput)

---

<a id="chl_identity_label"></a>

### `chl_identity_label`

`function` `const` | [include/chrome_layout.h:162](../../include/chrome_layout.h#L162)

```c
const char *chl_identity_label(chl_identity id);
```

Short English label for the badge (static, never NULL).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `id` | `chl_identity` |  |  |

**Returns:** `char *`

*Called by:* [`LLVMFuzzerTestOneInput`](fuzz.fuzz_chrome_layout.c.md#llvmfuzzertestoneinput)

---

## Macros

<a id="chl_pad"></a>

### `CHL_PAD`

`macro` | [include/chrome_layout.h:19](../../include/chrome_layout.h#L19)

```c
#define CHL_PAD
```

row 2: navigation buttons, URL pill, menu

---

<a id="chl_tab_top_gap"></a>

### `CHL_TAB_TOP_GAP`

`macro` | [include/chrome_layout.h:20](../../include/chrome_layout.h#L20)

```c
#define CHL_TAB_TOP_GAP
```

outer horizontal padding of both rows

---

<a id="chl_tab_min_w"></a>

### `CHL_TAB_MIN_W`

`macro` | [include/chrome_layout.h:21](../../include/chrome_layout.h#L21)

```c
#define CHL_TAB_MIN_W
```

space above a tab inside row 1

---

<a id="chl_tab_max_w"></a>

### `CHL_TAB_MAX_W`

`macro` | [include/chrome_layout.h:22](../../include/chrome_layout.h#L22)

```c
#define CHL_TAB_MAX_W
```

---

<a id="chl_tab_gap"></a>

### `CHL_TAB_GAP`

`macro` | [include/chrome_layout.h:23](../../include/chrome_layout.h#L23)

```c
#define CHL_TAB_GAP
```

---

<a id="chl_tab_close"></a>

### `CHL_TAB_CLOSE`

`macro` | [include/chrome_layout.h:24](../../include/chrome_layout.h#L24)

```c
#define CHL_TAB_CLOSE
```

space between two tabs

---

<a id="chl_tab_close_min_w"></a>

### `CHL_TAB_CLOSE_MIN_W`

`macro` | [include/chrome_layout.h:25](../../include/chrome_layout.h#L25)

```c
#define CHL_TAB_CLOSE_MIN_W
```

square close button inside a tab

---

<a id="chl_newtab_w"></a>

### `CHL_NEWTAB_W`

`macro` | [include/chrome_layout.h:26](../../include/chrome_layout.h#L26)

```c
#define CHL_NEWTAB_W
```

narrower inactive tabs hide their close button

---

<a id="chl_win_btn_w"></a>

### `CHL_WIN_BTN_W`

`macro` | [include/chrome_layout.h:27](../../include/chrome_layout.h#L27)

```c
#define CHL_WIN_BTN_W
```

---

<a id="chl_drag_min"></a>

### `CHL_DRAG_MIN`

`macro` | [include/chrome_layout.h:28](../../include/chrome_layout.h#L28)

```c
#define CHL_DRAG_MIN
```

---

<a id="chl_btn"></a>

### `CHL_BTN`

`macro` | [include/chrome_layout.h:29](../../include/chrome_layout.h#L29)

```c
#define CHL_BTN
```

CSD: drag area always kept free in row 1

---

<a id="chl_btn_gap"></a>

### `CHL_BTN_GAP`

`macro` | [include/chrome_layout.h:30](../../include/chrome_layout.h#L30)

```c
#define CHL_BTN_GAP
```

round toolbar button diameter

---

<a id="chl_id_w"></a>

### `CHL_ID_W`

`macro` | [include/chrome_layout.h:32](../../include/chrome_layout.h#L32)

```c
#define CHL_ID_W
```

---

<a id="chl_star_w"></a>

### `CHL_STAR_W`

`macro` | [include/chrome_layout.h:33](../../include/chrome_layout.h#L33)

```c
#define CHL_STAR_W
```

identity badge slot at the pill's left

---

<a id="chl_star_min_url"></a>

### `CHL_STAR_MIN_URL`

`macro` | [include/chrome_layout.h:34](../../include/chrome_layout.h#L34)

```c
#define CHL_STAR_MIN_URL
```

bookmark star slot at the pill's right

---

<a id="chl_more_w"></a>

### `CHL_MORE_W`

`macro` | [include/chrome_layout.h:35](../../include/chrome_layout.h#L35)

```c
#define CHL_MORE_W
```

narrower pills keep their width for the URL text

---

<a id="chl_drag_threshold"></a>

### `CHL_DRAG_THRESHOLD`

`macro` | [include/chrome_layout.h:36](../../include/chrome_layout.h#L36)

```c
#define CHL_DRAG_THRESHOLD
```

hidden-tabs indicator at each end of an overflowing strip

---

<a id="chl_find_field_w"></a>

### `CHL_FIND_FIELD_W`

`macro` | [include/chrome_layout.h:116](../../include/chrome_layout.h#L116)

```c
#define CHL_FIND_FIELD_W
```

bar height

---

<a id="chl_find_btn"></a>

### `CHL_FIND_BTN`

`macro` | [include/chrome_layout.h:118](../../include/chrome_layout.h#L118)

```c
#define CHL_FIND_BTN
```

---

<a id="chl_find_count_w"></a>

### `CHL_FIND_COUNT_W`

`macro` | [include/chrome_layout.h:119](../../include/chrome_layout.h#L119)

```c
#define CHL_FIND_COUNT_W
```

prev / next / close square buttons

---
