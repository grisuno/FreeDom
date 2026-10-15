# `gui/browser_ui.c`

> Source: [gui/browser_ui.c:1](../../gui/browser_ui.c#L1) | language `c` | coverage 31.9% | [API index](../index.md)

## Contents

- **Structs:** [`ui_menu_item`](#ui_menu_item), [`ui_input_state`](#ui_input_state), [`ui_image`](#ui_image), [`ui_bg_image`](#ui_bg_image), [`tab_ctx`](#tab_ctx), [`browser_window`](#browser_window), [`fetch_prep`](#fetch_prep), [`fetch_job`](#fetch_job), [`rc_frag`](#rc_frag), [`rc_row`](#rc_row), [`rc_box`](#rc_box), [`rc_oof_sub`](#rc_oof_sub), [`rc_layout`](#rc_layout), [`rc_oof_sub`](#rc_oof_sub), [`rc_open_box`](#rc_open_box), [`rc_state`](#rc_state), [`rc_ext`](#rc_ext), [`item_sides`](#item_sides), [`rc_defer_col`](#rc_defer_col), [`rc_defer`](#rc_defer), [`freebug_window`](#freebug_window)
- **Enums:** [`ui_menu_action`](#ui_menu_action), [`ui_hot`](#ui_hot), [`rc_rowkind`](#rc_rowkind)
- **Type Aliases:** [`bs`](#bs), [`freebug_window`](#freebug_window), [`allowlisted`](#allowlisted), [`font_size`](#font_size), [`kind`](#kind), [`h`](#h), [`block_id`](#block_id), [`line_desc`](#line_desc), [`family`](#family), [`key`](#key), [`col`](#col)
- **Functions:** [`offset`](#offset), [`fields`](#fields), [`gutter`](#gutter), [`proxy`](#proxy), [`layout`](#layout), [`GET`](#get), [`only`](#only), [`first`](#first), [`hb_is_allowlisted`](#hb_is_allowlisted), [`proceed`](#proceed), [`secure_fetch`](#secure_fetch), [`string`](#string), [`toggle`](#toggle), [`stylesheets`](#stylesheets), [`body`](#body), [`ALIVE`](#alive), [`arrives`](#arrives), [`strcmp`](#strcmp), [`resolve`](#resolve), [`HarfBuzz`](#harfbuzz), [`add`](#add), [`run`](#run), [`produced`](#produced), [`line`](#line), [`inlines`](#inlines), [`table`](#table), [`row`](#row), [`way`](#way), [`TABLE`](#table), [`axis`](#axis), [`slot`](#slot), [`struct`](#struct), [`path`](#path), [`own`](#own), [`items`](#items), [`children`](#children), [`behind`](#behind), [`column`](#column), [`columns`](#columns), [`treatment`](#treatment), [`context`](#context), [`x`](#x), [`thumbnail`](#thumbnail), [`yet`](#yet), [`chain`](#chain), [`anchor`](#anchor), [`key`](#key), [`have`](#have), [`standalone`](#standalone), [`it`](#it), [`count`](#count), [`approximation`](#approximation), [`margin`](#margin), [`rd_build`](#rd_build), [`dies`](#dies), [`descriptors`](#descriptors), [`again`](#again), [`blocking`](#blocking), [`video_stop`](#video_stop), [`upstream`](#upstream), [`rect`](#rect), [`text`](#text), [`spaced`](#spaced), [`layer`](#layer), [`cairo_set_dash`](#cairo_set_dash), [`cairo_set_dash`](#cairo_set_dash), [`cairo_set_dash`](#cairo_set_dash), [`cairo_set_dash`](#cairo_set_dash), [`convention`](#convention), [`set_rgb`](#set_rgb), [`cairo_set_dash`](#cairo_set_dash), [`cairo_set_dash`](#cairo_set_dash), [`cairo_set_dash`](#cairo_set_dash), [`cairo_set_dash`](#cairo_set_dash), [`bg`](#bg), [`rows`](#rows), [`fragment`](#fragment), [`the`](#the), [`limits`](#limits), [`fill`](#fill), [`compositing`](#compositing), [`box`](#box), [`caller`](#caller), [`ui_render_png`](#ui_render_png), [`origin`](#origin), [`ui_render_png_images`](#ui_render_png_images), [`ui_render_pdf_images`](#ui_render_pdf_images), [`ui_dump_layout`](#ui_dump_layout), [`in`](#in), [`Firefox`](#firefox), [`reference`](#reference), [`sf_ws_url_check`](#sf_ws_url_check), [`memory`](#memory), [`GET`](#get), [`presentation`](#presentation), [`resizes`](#resizes), [`wl_array_for_each`](#wl_array_for_each), [`element`](#element), [`down`](#down), [`loop`](#loop), [`ui_run_browser`](#ui_run_browser), [`saving`](#saving), [`redraws`](#redraws), [`applies`](#applies), [`flow`](#flow), [`cost`](#cost)
- **Macros:** [`_GNU_SOURCE`](#_gnu_source), [`UI_TAB_MIN_W`](#ui_tab_min_w), [`UI_TAB_MAX_W`](#ui_tab_max_w), [`UI_TAB_NEW_W`](#ui_tab_new_w), [`UI_TAB_CLOSE_W`](#ui_tab_close_w), [`UI_BTN_W`](#ui_btn_w), [`UI_WIN_BTN_W`](#ui_win_btn_w), [`UI_MARGIN`](#ui_margin), [`UI_BTN_LEFT`](#ui_btn_left), [`UI_LIST_INDENT`](#ui_list_indent), [`UI_SCROLLBAR_W`](#ui_scrollbar_w), [`UI_SCROLLBAR_MIN`](#ui_scrollbar_min), [`UI_SCROLLBAR_PAD`](#ui_scrollbar_pad), [`UI_RESIZE_MARGIN`](#ui_resize_margin), [`UI_MENU_W`](#ui_menu_w), [`UI_MENU_PAD`](#ui_menu_pad), [`UI_CHECK_SZ`](#ui_check_sz), [`UI_HAMBURGER_W`](#ui_hamburger_w), [`UI_HAMBURGER_GAP`](#ui_hamburger_gap), [`UI_CURSOR_SIZE`](#ui_cursor_size), [`UI_TOAST_PAD`](#ui_toast_pad), [`OMNI_MAX_SUGG`](#omni_max_sugg), [`UI_TWO_PI`](#ui_two_pi), [`UI_INPUT_PAD`](#ui_input_pad), [`UI_INPUT_MEASURE_W`](#ui_input_measure_w), [`UI_INPUT_WIDTH`](#ui_input_width), [`UI_BUTTON_HPAD`](#ui_button_hpad), [`UI_FORM_FIELDS_MAX`](#ui_form_fields_max), [`UI_UNDERLINE_OFFSET`](#ui_underline_offset), [`UI_UNDERLINE_THICK`](#ui_underline_thick), [`UI_STRIKE_OFFSET`](#ui_strike_offset), [`UI_OVERLINE_OFFSET`](#ui_overline_offset), [`UI_SLICE_MAX`](#ui_slice_max), [`UI_MENU_COUNT`](#ui_menu_count), [`UI_IMAGE_MAX_BODY`](#ui_image_max_body), [`UI_MAX_TABS`](#ui_max_tabs), [`UI_READER_COLUMN_W`](#ui_reader_column_w), [`FONT_STASH_MAX_SHEETS`](#font_stash_max_sheets), [`FONT_STASH_MAX_BYTES`](#font_stash_max_bytes), [`JS_NAV_MAX`](#js_nav_max), [`HIST_STEP_DEPTH_MAX`](#hist_step_depth_max), [`JS_TICKS_PER_LOAD`](#js_ticks_per_load), [`UI_RELOAD_X`](#ui_reload_x), [`RC_BOX_STACK_MAX`](#rc_box_stack_max), [`RC_FLOAT_MAX`](#rc_float_max), [`RC_FLOAT_FIT_MIN`](#rc_float_fit_min), [`FLEX_MEASURE_W`](#flex_measure_w), [`FLEX_MIN_MEASURE_W`](#flex_min_measure_w), [`RC_MAX_OUT_OF_FLOW`](#rc_max_out_of_flow), [`RC_DEFER_COLS`](#rc_defer_cols), [`RC_DEFER_RANGES`](#rc_defer_ranges), [`RC_DEFER_BAND_RUNS`](#rc_defer_band_runs), [`BUI_CONIC_SLICES`](#bui_conic_slices), [`OV_MAX_DEPTH`](#ov_max_depth), [`H2R`](#h2r), [`PDF_PAGE_W`](#pdf_page_w), [`PDF_MARGIN`](#pdf_margin), [`PNG_PAGE_W`](#png_page_w), [`PNG_MARGIN`](#png_margin), [`FBW_W`](#fbw_w), [`FBW_HEADER`](#fbw_header), [`FBW_PAD`](#fbw_pad), [`FBW_LINE`](#fbw_line), [`FBW_GUTTER`](#fbw_gutter), [`FBW_MIN_SPLIT`](#fbw_min_split), [`FBW_MAX_SPLIT`](#fbw_max_split), [`FBW_COPY_BTN_W`](#fbw_copy_btn_w)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class ui_menu_action
    <<enum>> ui_menu_action
    class ui_menu_item
    <<struct>> ui_menu_item
    class ui_hot
    <<enum>> ui_hot
    class ui_input_state
    <<struct>> ui_input_state
    class ui_image
    <<struct>> ui_image
    class ui_bg_image
    <<struct>> ui_bg_image
    class bs
    <<type_alias>> bs
    class tab_ctx
    <<struct>> tab_ctx
    class browser_window
    <<struct>> browser_window
    browser_window : delay()
    browser_window : main()
    class freebug_window
    <<type_alias>> freebug_window
    class allowlisted
    <<type_alias>> allowlisted
    class fetch_prep
    <<struct>> fetch_prep
    class fetch_job
    <<struct>> fetch_job
    class font_size
    <<type_alias>> font_size
    class rc_frag
    <<struct>> rc_frag
    class rc_rowkind
    <<enum>> rc_rowkind
    class kind
    <<type_alias>> kind
    class rc_row
    <<struct>> rc_row
    class h
    <<type_alias>> h
    class rc_box
    <<struct>> rc_box
    rc_box : smaller()
    class rc_oof_sub
    <<struct>> rc_oof_sub
    class rc_layout
    <<struct>> rc_layout
    class rc_oof_sub
    <<struct>> rc_oof_sub
    class block_id
    <<type_alias>> block_id
```

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_gui_browser_ui_c__proxy(["proxy"])
    n_gui_browser_ui_c__strcmp(["strcmp"])
    n_gui_browser_ui_c__first(["first"])
    n_gui_browser_ui_c__proceed(["proceed"])
    n_gui_browser_ui_c__hb_is_allowlisted(["hb_is_allowlisted"])
    n_gui_browser_ui_c__toggle(["toggle"])
    n_gui_browser_ui_c__arrives(["arrives"])
    n_gui_browser_ui_c__RC_FLOAT_FIT_MIN(["RC_FLOAT_FIT_MIN"])
    n_gui_browser_ui_c__line(["line"])
    n_gui_browser_ui_c__margin(["margin"])
    n_gui_browser_ui_c__offset(["offset"])
    n_include_box_style_h__page["box_style.page"]
    n_include_link_nav_h__action["link_nav.action"]
    n_include_prefs_h__free["prefs.free"]
    n_include_secure_fetch_h__policy["secure_fetch.policy"]
    n_gui_browser_ui_c__UI_MAX_TABS(["UI_MAX_TABS"])
    n_src_css_c__NULL["css.NULL"]
    n_gui_browser_ui_c__UI_READER_COLUMN_W(["UI_READER_COLUMN_W"])
    n_gui_bui_theme_c__ui_theme_for["bui_theme.ui_theme_for"]
    n_include_zoom_h__zm_apply["zoom.zm_apply"]
    n_include_zoom_h__zm_scale["zoom.zm_scale"]
    n_gui_browser_ui_c__GET(["GET"])
    n_include_secure_fetch_h__sf_response_free["secure_fetch.sf_response_free"]
    n_src_secure_fetch_c__sf_post["secure_fetch.sf_post"]
    n_gui_browser_ui_c__FONT_STASH_MAX_BYTES(["FONT_STASH_MAX_BYTES"])
    n_gui_browser_ui_c__only(["only"])
    n_src_css_color_c__strncmp["css_color.strncmp"]
    n_src_link_nav_c__ln_resolve["link_nav.ln_resolve"]
    n_include_text_shape_h__tsh_webfont_clear["text_shape.tsh_webfont_clear"]
    n_src_webfont_load_c__wf_load_document["webfont_load.wf_load_document"]
    n_gui_browser_ui_c__proxy --> n_gui_browser_ui_c__strcmp
    n_gui_browser_ui_c__first --> n_gui_browser_ui_c__strcmp
    n_gui_browser_ui_c__proceed --> n_gui_browser_ui_c__hb_is_allowlisted
    n_gui_browser_ui_c__toggle --> n_gui_browser_ui_c__hb_is_allowlisted
    n_gui_browser_ui_c__arrives --> n_gui_browser_ui_c__strcmp
    n_gui_browser_ui_c__RC_FLOAT_FIT_MIN --> n_gui_browser_ui_c__line
    n_gui_browser_ui_c__RC_FLOAT_FIT_MIN --> n_gui_browser_ui_c__margin
    n_gui_browser_ui_c__offset -.-> n_include_box_style_h__page
    n_gui_browser_ui_c__offset -.-> n_include_link_nav_h__action
    n_gui_browser_ui_c__offset -.-> n_include_prefs_h__free
    n_gui_browser_ui_c__offset -.-> n_include_secure_fetch_h__policy
    n_gui_browser_ui_c__UI_MAX_TABS -.-> n_src_css_c__NULL
    n_gui_browser_ui_c__UI_READER_COLUMN_W -.-> n_gui_bui_theme_c__ui_theme_for
    n_gui_browser_ui_c__UI_READER_COLUMN_W -.-> n_include_zoom_h__zm_apply
    n_gui_browser_ui_c__UI_READER_COLUMN_W -.-> n_include_zoom_h__zm_scale
    n_gui_browser_ui_c__GET -.-> n_include_secure_fetch_h__sf_response_free
    n_gui_browser_ui_c__GET -.-> n_src_secure_fetch_c__sf_post
    n_gui_browser_ui_c__FONT_STASH_MAX_BYTES -.-> n_include_prefs_h__free
    n_gui_browser_ui_c__only -.-> n_include_prefs_h__free
    n_gui_browser_ui_c__only -.-> n_src_css_color_c__strncmp
    n_gui_browser_ui_c__only -.-> n_src_link_nav_c__ln_resolve
    n_gui_browser_ui_c__first -.-> n_include_prefs_h__free
    n_gui_browser_ui_c__first -.-> n_include_text_shape_h__tsh_webfont_clear
    n_gui_browser_ui_c__first -.-> n_src_webfont_load_c__wf_load_document
```

## Structs

<a id="ui_menu_item"></a>

### `ui_menu_item`

`struct` | [gui/browser_ui.c:179](../../gui/browser_ui.c#L179)

```c
typedef struct ui_menu_item
```

---

<a id="ui_input_state"></a>

### `ui_input_state`

`struct` | [gui/browser_ui.c:217](../../gui/browser_ui.c#L217)

```c
typedef struct ui_input_state
```

Live editable state for one form text control, aliasing a block of the current rd_doc (not owned; valid until the doc is replaced).

The field carries the value the user is editing; submission reads it back.

---

<a id="ui_image"></a>

### `ui_image`

`struct` | [gui/browser_ui.c:241](../../gui/browser_ui.c#L241)

```c
typedef struct ui_image
```

href is an OWNED copy of the image's URL, not a pointer into w->doc (fixed 2026-07-16): a worker result applied outside a fresh navigation (a click, or a JS timer firing via OP_TICK -- see apply_click_result) rebuilds w->doc WHOLESALE from scratch without re-running load_images, so any rd_block* recorded here would immediately dangle and, worse, silently stop matching ANY block in the new doc (find_image compared pointer identity) -- every already-decoded image would revert to its placeholder on the very next repaint even though nothing about the image actually changed.

Matching by URL content instead is stable across a doc rebuild with no re-fetch needed (the decoded surface is reused as-is): a JS timer firing seconds into a page like an ad-heavy anime-streaming site is exactly the case this fixes.

---

<a id="ui_bg_image"></a>

### `ui_bg_image`

`struct` | [gui/browser_ui.c:254](../../gui/browser_ui.c#L254)

```c
typedef struct ui_bg_image
```

A decoded CSS background-image for one box of the current doc (2026-07-16).

Same shape as ui_image and the same reasoning applies: url is an OWNED copy (not a pv_box_def* into w->doc), so it survives a doc rebuild that does not re-run load_bg_images. surface NULL means blocked/unset/failed (paint as if there were no background-image at all, no placeholder: it is decoration, not content with alt text, matching real-browser behaviour for a failed background).

---

<a id="tab_ctx"></a>

### `tab_ctx`

`struct` | [gui/browser_ui.c:271](../../gui/browser_ui.c#L271)

```c
typedef struct tab_ctx
```

One tab's complete per-page state: everything that must persist when the tab is not the foreground one.

The browser_window keeps the ACTIVE tab's copy in its own fields (so the 200+ render/event call sites stay unchanged); tab_save/tab_restore move this set in and out of the slot array on a switch. All owned pointers are transferred by value (no deep copy, no free): exactly one of {live window field, inactive slot} owns each allocation at any time.

---

<a id="browser_window"></a>

### `browser_window`

`struct` | [gui/browser_ui.c:287](../../gui/browser_ui.c#L287)

```c
typedef struct browser_window
```

**Members**

| Member | Kind | Summary |
|---|---|---|
| [`delay`](#browser_window-delay) | method |  |
| [`main`](#browser_window-main) | method |  |

<a id="browser_window-delay"></a>

#### `browser_window.delay`

`method` | [gui/browser_ui.c:361](../../gui/browser_ui.c#L361)

```c
* timer delay (tab_page.next_timer_ms);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `next_timer_ms` | `tab_page.` |  |  |

**Returns:** `* timer`

<a id="browser_window-main"></a>

#### `browser_window.main`

`method` | [gui/browser_ui.c:504](../../gui/browser_ui.c#L504)

```c
* * Feeder thread: downloads TS segments and writes them to the decoder pipe * so the main (Wayland) thread never blocks on HTTP. The thread is spawned by * video_play() and joined by video_stop();
```

**Returns:** `* * Feeder thread: downloads TS segments and writes them to the decoder pipe * so the`

---

<a id="fetch_prep"></a>

### `fetch_prep`

`struct` | [gui/browser_ui.c:1664](../../gui/browser_ui.c#L1664)

```c
typedef struct fetch_prep
```

Outcome of the pre-fetch gates shared by GET (do_load) and POST (do_submit_post).

Both MUST pass through the SAME host filter, per-host exception, allowlist override and Tor/I2P realm route before any socket opens -- otherwise a POST could reach the network under laxer rules than a GET, or leak a .onion lookup over clearnet.

---

<a id="fetch_job"></a>

### `fetch_job`

`struct` | [gui/browser_ui.c:1745](../../gui/browser_ui.c#L1745)

```c
typedef struct fetch_job
```

A network request handed to the fetch thread.

It owns deep copies of every input string (the window's buffers may change while the fetch runs), and is filled with the result before being posted back to the main thread, which owns it from then on. The thread ONLY accesses the browser_window's stream_* fields (under stream_lock) and the fetch_pipe/stream_evfd for I/O -- never any other field.

---

<a id="rc_frag"></a>

### `rc_frag`

`struct` | [gui/browser_ui.c:3080](../../gui/browser_ui.c#L3080)

```c
typedef struct rc_frag
```

---

<a id="rc_row"></a>

### `rc_row`

`struct` | [gui/browser_ui.c:3143](../../gui/browser_ui.c#L3143)

```c
typedef struct rc_row
```

---

<a id="rc_box"></a>

### `rc_box`

`struct` | [gui/browser_ui.c:3162](../../gui/browser_ui.c#L3162)

```c
typedef struct rc_box
```

One painted block box (Hito 23b-8 Step C): a border-box rectangle in layout space with its author decoration, painted behind the rows it encloses.

Built from a maximal run of rd_blocks sharing one block_id. block_id is stamped at open_box time so position_doc can map an in-flow rc_box back to its pv_box_def (and the resolved out-of-flow rect to the right ancestor).

**Members**

| Member | Kind | Summary |
|---|---|---|
| [`smaller`](#rc_box-smaller) | method |  |

<a id="rc_box-smaller"></a>

#### `rc_box.smaller`

`method` | [gui/browser_ui.c:3184](../../gui/browser_ui.c#L3184)

```c
* size when the content is smaller (height) or wider (min-width);
```

**Returns:** `* size when the content is`

---

<a id="rc_oof_sub"></a>

### `rc_oof_sub`

`struct` | [gui/browser_ui.c:3213](../../gui/browser_ui.c#L3213)

```c
struct rc_oof_sub;
```

---

<a id="rc_layout"></a>

### `rc_layout`

`struct` | [gui/browser_ui.c:3215](../../gui/browser_ui.c#L3215)

```c
typedef struct rc_layout
```

---

<a id="rc_oof_sub"></a>

### `rc_oof_sub`

`struct` | [gui/browser_ui.c:3253](../../gui/browser_ui.c#L3253)

```c
typedef struct rc_oof_sub
```

One out-of-flow subtree's own layout and where it lands on the page.

---

<a id="rc_open_box"></a>

### `rc_open_box`

`struct` | [gui/browser_ui.c:3263](../../gui/browser_ui.c#L3263)

```c
typedef struct rc_open_box
```

Box engine (Hito 23b-8 Step D): one entry of the open-box stack.

A box's content rect (inner_left/inner_w) is the coordinate context its children (text or nested boxes) are placed in; bl/br/pb/bb are its borders/bottom-padding reserved geometry; box_idx points at the rc_box rect being measured.

---

<a id="rc_state"></a>

### `rc_state`

`struct` | [gui/browser_ui.c:3321](../../gui/browser_ui.c#L3321)

```c
typedef struct rc_state
```

---

<a id="rc_ext"></a>

### `rc_ext`

`struct` | [gui/browser_ui.c:3912](../../gui/browser_ui.c#L3912)

```c
typedef struct rc_ext
```

Author text-presentation extensions for a block, derived from its rd_block (already gated by caps.css upstream) and handed to flow_text.

---

<a id="item_sides"></a>

### `item_sides`

`struct` | [gui/browser_ui.c:4759](../../gui/browser_ui.c#L4759)

```c
typedef struct item_sides
```

Padding + border edges (px) of a flex/grid item's ROOT box, plus that box's index (-1 when the item carries none: table cells, author CSS off).

Extracted so the auto-basis measuring pre-pass and the flow loop below cannot drift on what an item's content inset is.

**Members**

| Member | Kind | Summary |
|---|---|---|
| [`mr`](#item_sides-mr) | type_alias | Padding + border edges (px) of a flex/grid item's ROOT box, plus that box's index (-1 when the item carries none: table cells, author CSS off). |

<a id="item_sides-mr"></a>

#### `item_sides.mr`

`type_alias` | [gui/browser_ui.c:4759](../../gui/browser_ui.c#L4759)

```c
typedef struct item_sides { double ml, mr;
```

Padding + border edges (px) of a flex/grid item's ROOT box, plus that box's index (-1 when the item carries none: table cells, author CSS off).

Extracted so the auto-basis measuring pre-pass and the flow loop below cannot drift on what an item's content inset is.

---

<a id="rc_defer_col"></a>

### `rc_defer_col`

`struct` | [gui/browser_ui.c:6826](../../gui/browser_ui.c#L6826)

```c
typedef struct rc_defer_col
```

---

<a id="rc_defer"></a>

### `rc_defer`

`struct` | [gui/browser_ui.c:6833](../../gui/browser_ui.c#L6833)

```c
typedef struct rc_defer
```

---

<a id="freebug_window"></a>

### `freebug_window`

`struct` | [gui/browser_ui.c:14084](../../gui/browser_ui.c#L14084)

```c
struct freebug_window
```

---

## Enums

<a id="ui_menu_action"></a>

### `ui_menu_action`

`enum` | [gui/browser_ui.c:162](../../gui/browser_ui.c#L162)

```c
typedef enum ui_menu_action
```

The options-menu items.

A capability item toggles a bool in rdp_caps by field offset (labels and the flag live in one place, no magic indices); a theme item selects a palette; the force item ignores author colours.

---

<a id="ui_hot"></a>

### `ui_hot`

`enum` | [gui/browser_ui.c:210](../../gui/browser_ui.c#L210)

```c
typedef enum ui_hot
```

Toolbar control under the pointer, for the hover highlight (the same affordance links already get).

---

<a id="rc_rowkind"></a>

### `rc_rowkind`

`enum` | [gui/browser_ui.c:3141](../../gui/browser_ui.c#L3141)

```c
typedef enum rc_rowkind { RC_TEXT = 0, RC_IMAGE, RC_INPUT, RC_VIDEO, RC_SVG } rc_rowkind;
```

---

## Type Aliases

<a id="bs"></a>

### `bs`

`type_alias` | [gui/browser_ui.c:271](../../gui/browser_ui.c#L271)

```c
typedef struct tab_ctx { browser_state bs;
```

One tab's complete per-page state: everything that must persist when the tab is not the foreground one.

The browser_window keeps the ACTIVE tab's copy in its own fields (so the 200+ render/event call sites stay unchanged); tab_save/tab_restore move this set in and out of the slot array on a switch. All owned pointers are transferred by value (no deep copy, no free): exactly one of {live window field, inactive slot} owns each allocation at any time.

---

<a id="freebug_window"></a>

### `freebug_window`

`type_alias` | [gui/browser_ui.c:559](../../gui/browser_ui.c#L559)

```c
typedef struct freebug_window freebug_window;
```

Freebug second-window forward declarations (defined further down, but referenced by render_current_ex, the menu and the input listeners above their definition).

---

<a id="allowlisted"></a>

### `allowlisted`

`type_alias` | [gui/browser_ui.c:1664](../../gui/browser_ui.c#L1664)

```c
typedef struct fetch_prep { int allowlisted;
```

Outcome of the pre-fetch gates shared by GET (do_load) and POST (do_submit_post).

Both MUST pass through the SAME host filter, per-host exception, allowlist override and Tor/I2P realm route before any socket opens -- otherwise a POST could reach the network under laxer rules than a GET, or leak a .onion lookup over clearnet.

---

<a id="font_size"></a>

### `font_size`

`type_alias` | [gui/browser_ui.c:3079](../../gui/browser_ui.c#L3079)

```c
typedef struct rc_frag { double x, width, font_size;
```

The content area paints an rd_doc (the same structured document the headless mode prints): headings, paragraphs and inline links flow word-by-word into lines, the image-tracking warning is a banner, and each image is a bordered placeholder showing its render_policy decision.

Layout runs once per frame into transient arrays so vertical scrolling can be a smooth pixel offset over the real total height. This is visual-only (no headless test) but compiles under the same hardened flags.

---

<a id="kind"></a>

### `kind`

`type_alias` | [gui/browser_ui.c:3142](../../gui/browser_ui.c#L3142)

```c
typedef struct rc_row { rc_rowkind kind;
```

---

<a id="h"></a>

### `h`

`type_alias` | [gui/browser_ui.c:3162](../../gui/browser_ui.c#L3162)

```c
typedef struct rc_box { double x, top, w, h;
```

One painted block box (Hito 23b-8 Step C): a border-box rectangle in layout space with its author decoration, painted behind the rows it encloses.

Built from a maximal run of rd_blocks sharing one block_id. block_id is stamped at open_box time so position_doc can map an in-flow rc_box back to its pv_box_def (and the resolved out-of-flow rect to the right ancestor).

---

<a id="block_id"></a>

### `block_id`

`type_alias` | [gui/browser_ui.c:3263](../../gui/browser_ui.c#L3263)

```c
typedef struct rc_open_box { int block_id;
```

Box engine (Hito 23b-8 Step D): one entry of the open-box stack.

A box's content rect (inner_left/inner_w) is the coordinate context its children (text or nested boxes) are placed in; bl/br/pb/bb are its borders/bottom-padding reserved geometry; box_idx points at the rc_box rect being measured.

---

<a id="line_desc"></a>

### `line_desc`

`type_alias` | [gui/browser_ui.c:3320](../../gui/browser_ui.c#L3320)

```c
typedef struct rc_state { double cur_top, pending_gap, pen_x, line_asc, line_desc;
```

Narrowest strip beside a float that still counts as room for a line box.

Below it the line is shifted under the float instead (CSS 2.1 9.5). It is a width in px, not a heuristic about content: a strip narrower than one average word cannot hold a line box, and pretending it can is what makes text paint * on top of the float. define RC_FLOAT_FIT_MIN 32.0

---

<a id="family"></a>

### `family`

`type_alias` | [gui/browser_ui.c:3912](../../gui/browser_ui.c#L3912)

```c
typedef struct rc_ext { int family;
```

Author text-presentation extensions for a block, derived from its rd_block (already gated by caps.css upstream) and handed to flow_text.

---

<a id="key"></a>

### `key`

`type_alias` | [gui/browser_ui.c:6826](../../gui/browser_ui.c#L6826)

```c
typedef struct rc_defer_col { int key;
```

---

<a id="col"></a>

### `col`

`type_alias` | [gui/browser_ui.c:6833](../../gui/browser_ui.c#L6833)

```c
typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];
```

---

## Functions

<a id="offset"></a>

### `offset`

`function` | [gui/browser_ui.c:160](../../gui/browser_ui.c#L160)

```c
* offset (labels and the flag live in one place, no magic indices);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `place` | `labels and the flag live in one` |  |  |
| `indices` | `no magic` |  |  |

**Returns:** `*`

*Calls:* [`page`](include.box_style.h.md#page), [`action`](include.link_nav.h.md#action), [`free`](include.prefs.h.md#free), [`policy`](include.secure_fetch.h.md#policy)

---

<a id="fields"></a>

### `fields`

`function` | [gui/browser_ui.c:267](../../gui/browser_ui.c#L267)

```c
* fields (so the 200+ render/event call sites stay unchanged);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `unchanged` | `so the 200+ render/event call sites stay` |  |  |

**Returns:** `*`

---

<a id="gutter"></a>

### `gutter`

`function` | [gui/browser_ui.c:578](../../gui/browser_ui.c#L578)

```c
* gutter (content_margin) is intentionally left unzoomed, like a browser's text * zoom. The PDF ...
```

**Returns:** `*`

---

<a id="proxy"></a>

### `proxy`

`function` | [gui/browser_ui.c:1007](../../gui/browser_ui.c#L1007)

```c
* and enable each proxy ("1" => the default port);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `port` | `"1" => the default` |  |  |

**Returns:** `* and enable each`

*Calls:* [`strcmp`](#strcmp)

*Called by:* [`EXIT_USAGE`](src.freedom.c.md#exit_usage)

---

<a id="layout"></a>

### `layout`

`function` | [gui/browser_ui.c:1153](../../gui/browser_ui.c#L1153)

```c
* shared by layout (row height) and paint (blit), so they cannot drift apart. */ static int image...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `height` | `row` |  |  |

**Returns:** `* shared by`

---

<a id="get"></a>

### `GET`

`function` | [gui/browser_ui.c:1370](../../gui/browser_ui.c#L1370)

```c
* a GET (Zero Trust). cfg->policy is restored before returning. */ static sf_status fetch_post_na...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `Trust` | `Zero` |  |  |

**Returns:** `* a`

*Calls:* [`sf_response_free`](include.secure_fetch.h.md#sf_response_free), [`sf_post`](src.secure_fetch.c.md#sf_post)

---

<a id="only"></a>

### `only`

`function` | [gui/browser_ui.c:1490](../../gui/browser_ui.c#L1490)

```c
* Trusted pages only (untrusted CSS is still applied by the worker, but its * fonts never reach the parent registry). The raw worker URL is resolved to an * absolute https sheet URL here (the loader's
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `worker` | `untrusted CSS is still applied by the` |  |  |
| `registry` | `but its * fonts never reach the parent` |  |  |

**Returns:** `* Trusted pages`

*Calls:* [`free`](include.prefs.h.md#free), [`strncmp`](src.css_color.c.md#strncmp), [`ln_resolve`](src.link_nav.c.md#ln_resolve)

---

<a id="first"></a>

### `first`

`function` | [gui/browser_ui.c:1563](../../gui/browser_ui.c#L1563)

```c
* Navigation: clear the registry first (faces are per document). Untrusted: * no-op (fetch NULL)...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `document` | `faces are per` |  |  |

**Returns:** `* Navigation: clear the registry`

*Calls:* [`strcmp`](#strcmp), [`free`](include.prefs.h.md#free), [`tsh_webfont_clear`](include.text_shape.h.md#tsh_webfont_clear), [`wf_load_document`](src.webfont_load.c.md#wf_load_document)

---

<a id="hb_is_allowlisted"></a>

### `hb_is_allowlisted`

`function` | [gui/browser_ui.c:1627](../../gui/browser_ui.c#L1627)

```c
&& hb_is_allowlisted(w->hosts, ihost);
```

1 iff a domain suffix of host is explicitly on the allowlist (covers subdomains), else 0.

Distinct from hb_check: this reports an EXPLICIT allowlist entry, not the "allowed because nothing blocks it" default. The orchestrator uses it as the user's sovereign per-host override -- e.g. to navigate a site below Freedom's TLS standard. s/host NULL, empty, or longer than 253 chars => 0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `hosts` | `w->` |  |  |

**Returns:** `&&`

> **Inherited:** Documentation from [`hb_is_allowlisted`](#hb_is_allowlisted) (include/hostblock.h:75).

*Called by:* [`proceed`](#proceed), [`toggle`](#toggle)

---

<a id="proceed"></a>

### `proceed`

`function` | [gui/browser_ui.c:1670](../../gui/browser_ui.c#L1670)

```c
* may proceed (cfg and pr->allowlisted are then set);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `set` | `cfg and pr->allowlisted are then` |  |  |

**Returns:** `* may`

*Calls:* [`hb_is_allowlisted`](#hb_is_allowlisted), [`domain`](include.anti_fp.h.md#domain), [`browser_is_exception`](include.browser.h.md#browser_is_exception), [`nr_realm_name`](include.net_realm.h.md#nr_realm_name), [`tf_text`](include.textfield.h.md#tf_text), [`ti_should_impersonate`](include.tls_impersonate.h.md#ti_should_impersonate), [`hb_check`](src.hostblock.c.md#hb_check), [`nr_classify_url`](src.net_realm.c.md#nr_classify_url)

---

<a id="secure_fetch"></a>

### `secure_fetch`

`function` | [gui/browser_ui.c:1921](../../gui/browser_ui.c#L1921)

```c
* through secure_fetch (Zero Trust);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `Trust` | `Zero` |  |  |

**Returns:** `* through`

---

<a id="string"></a>

### `string`

`function` | [gui/browser_ui.c:2069](../../gui/browser_ui.c#L2069)

```c
* or an empty string (unset, blocked, or off by caps.images), so there is no * decision to re-check, unlike load_images which still reads b->img_decision (a * box def carries no decision field, only t
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `images` | `or off by caps.` |  |  |

**Returns:** `* or an empty`

*Calls:* [`du_is_data_url`](include.data_url.h.md#du_is_data_url), [`rd_box_at`](include.render_doc.h.md#rd_box_at), [`rd_box_count`](include.render_doc.h.md#rd_box_count)

---

<a id="toggle"></a>

### `toggle`

`function` | [gui/browser_ui.c:2126](../../gui/browser_ui.c#L2126)

```c
* No network: a capability toggle (images/CSS) re-renders from cache. Does nothing * when there is no cached source (start/error pages stay in plain-text mode). * * allow_js_nav: on a FRESH load (not
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `CSS` | `images/` |  |  |

**Returns:** `* No network: a capability`

*Calls:* [`hb_is_allowlisted`](#hb_is_allowlisted)

---

<a id="stylesheets"></a>

### `stylesheets`

`function` | [gui/browser_ui.c:2276](../../gui/browser_ui.c#L2276)

```c
* External stylesheets (Hito 27) follow the author-styles opt-in -- or the * trusted-host doctrine (Hito 28) -- (GET-only at the parent gate);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `Hito` |  |  |  |

**Returns:** `* External`

*Calls:* [`wc_derive`](src.webcaps.c.md#wc_derive)

---

<a id="body"></a>

### `body`

`function` | [gui/browser_ui.c:2319](../../gui/browser_ui.c#L2319)

```c
* every served CSS body (serial and pool paths alike). */ font_stash_reset(w);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `alike` | `serial and pool paths` |  |  |

**Returns:** `* every served CSS`

---

<a id="alive"></a>

### `ALIVE`

`function` | [gui/browser_ui.c:2427](../../gui/browser_ui.c#L2427)

```c
* keep the worker ALIVE (tab_worker) so the console REPL can tab_eval against this * live page. The next render (or a tab switch) closes it. */ fb_buffer_free(&w->console);
```

**Returns:** `* keep the worker`

---

<a id="arrives"></a>

### `arrives`

`function` | [gui/browser_ui.c:2513](../../gui/browser_ui.c#L2513)

```c
* on screen until the result arrives (deliver_fetch_result renders it). about:blank * and local ...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `it` | `deliver_fetch_result renders` |  |  |

**Returns:** `* on screen until the result`

*Calls:* [`strcmp`](#strcmp), [`browser_set_page`](include.browser.h.md#browser_set_page), [`free`](include.prefs.h.md#free), [`rp_host_of`](include.request_policy.h.md#rp_host_of), [`url_file_path`](include.url.h.md#url_file_path), [`browser_set_url_bar`](src.browser.c.md#browser_set_url_bar), [`prefs_bookmarks_page`](src.prefs.c.md#prefs_bookmarks_page), [`url_extract_userinfo`](src.url.c.md#url_extract_userinfo), [`url_is_file`](src.url.c.md#url_is_file), [`url_search_rewrite`](src.url.c.md#url_search_rewrite)

---

<a id="strcmp"></a>

### `strcmp`

`function` | [gui/browser_ui.c:2581](../../gui/browser_ui.c#L2581)

```c
&& strcmp(auth_host_buf, w->auth_host) != 0)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `auth_host` | `w->` |  |  |

**Returns:** `&&`

*Calls:* [`free`](include.prefs.h.md#free)

*Called by:* [`arrives`](#arrives), [`first`](#first), [`proxy`](#proxy), [`bx_ua_of_tag`](src.box_style.c.md#bx_ua_of_tag), [`ignored`](src.css.c.md#ignored), [`cc_parse`](src.css_color.c.md#cc_parse), [`strncmp`](src.css_color.c.md#strncmp), [`gradient`](src.css_gradient.c.md#gradient), [`csel_ident_eq`](src.css_select.c.md#csel_ident_eq), [`dl_ext_for_type`](src.download.c.md#dl_ext_for_type), [`dl_should_download`](src.download.c.md#dl_should_download), [`gets`](src.freedom.c.md#gets) and 14 more

---

<a id="resolve"></a>

### `resolve`

`function` | [gui/browser_ui.c:2615](../../gui/browser_ui.c#L2615)

```c
* origin so its relative references and local images resolve (confined to the * document's directory) -- a local page "acts like https" for resolution. */ clear_doc(w);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `directory` | `confined to the * document's` |  |  |

**Returns:** `* origin so its relative references and images`

*Called by:* [`im_parse`](src.import_map.c.md#im_parse), [`im_resolve`](src.import_map.c.md#im_resolve)

---

<a id="harfbuzz"></a>

### `HarfBuzz`

`function` | [gui/browser_ui.c:3577](../../gui/browser_ui.c#L3577)

```c
* descriptor via HarfBuzz (text_shape);
```

**Returns:** `* descriptor via`

---

<a id="add"></a>

### `add`

`function` | [gui/browser_ui.c:3762](../../gui/browser_ui.c#L3762)

```c
* about to add (top/h passed in). A box that survived a line wrap simply ends at the * wrap -- m...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `in` | `top/h passed` |  |  |

**Returns:** `* about to`

---

<a id="run"></a>

### `run`

`function` | [gui/browser_ui.c:3797](../../gui/browser_ui.c#L3797)

```c
* continuation run (block_id < 0 with no block break) deliberately skips reconcile * to stay on ...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `break` | `block_id < 0 with no block` |  |  |

**Returns:** `* continuation`

---

<a id="produced"></a>

### `produced`

`function` | [gui/browser_ui.c:3995](../../gui/browser_ui.c#L3995)

```c
* href tags every fragment produced (NULL for non-link runs) so a later hit-test * can recover the click target without re-walking the document. node_id tags the * originating element for JS click dis
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `runs` | `NULL for non-link` |  |  |

**Returns:** `* href tags every fragment`

---

<a id="line"></a>

### `line`

`function` | [gui/browser_ui.c:4079](../../gui/browser_ui.c#L4079)

```c
* its neighbours on the line (spec/page_view.md "Colapso de espacio en el borde * entre runs"). Read from src, the same buffer the loop scans, so a tab-expanded * <pre> agrees with itself. */ int star
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `runs` | `spec/page_view.md "Colapso de espacio en el borde * entre "` |  |  |

**Returns:** `* its neighbours on the`

*Called by:* [`RC_FLOAT_FIT_MIN`](#rc_float_fit_min)

---

<a id="inlines"></a>

### `inlines`

`function` | [gui/browser_ui.c:4307](../../gui/browser_ui.c#L4307)

```c
* atomic inlines (`<img><img><img>`, collapsing blanks skipped) share one line * and wrap like words (CSS 2.1 9.2.2) instead of stacking one row each. Returns * that next run's index, or 0 when the element is not followed by inline flow. */ static size_t replaced_opens_inline_line(const rd_doc *doc, size_t i)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `img` | `` `<img><img>< >` `` |  |  |
| `skipped` | `collapsing blanks` |  |  |

**Returns:** `* atomic`

*Calls:* [`rd_at`](include.render_doc.h.md#rd_at), [`rd_count`](include.render_doc.h.md#rd_count)

---

<a id="table"></a>

### `table`

`function` | [gui/browser_ui.c:4861](../../gui/browser_ui.c#L4861)

```c
* synthesised table (no descriptors to disagree) keeps the stamp. */ if (cd != NULL && !c...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `disagree` | `no descriptors to` |  |  |

**Returns:** `* synthesised`

*Calls:* [`rd_at`](include.render_doc.h.md#rd_at), [`rd_box_at`](include.render_doc.h.md#rd_box_at)

---

<a id="row"></a>

### `row`

`function` | [gui/browser_ui.c:4921](../../gui/browser_ui.c#L4921)

```c
* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */ static d...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `md` | `spec/page_view.` |  |  |
| `slashdot` | `jkanime/` |  |  |

**Returns:** `* label beside them shrank to one word per`

---

<a id="way"></a>

### `way`

`function` | [gui/browser_ui.c:4962](../../gui/browser_ui.c#L4962)

```c
* intrinsic box either way (it does not wrap below its own size). */ static int block_leaves_flow(const rd_doc *doc, const rd_block *bk);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `size` | `it does not wrap below its own` |  |  |

**Returns:** `* intrinsic box either`

---

<a id="table"></a>

### `TABLE`

`function` | [gui/browser_ui.c:5242](../../gui/browser_ui.c#L5242)

```c
* container TABLE (rd_cont_at) rather than from the head run, because a container * whose children are all containers has no run of its own to read them from -- that * is the whole reason the table ex
```

**Returns:** `* container`

*Calls:* [`bt_oof_root`](include.box_tree.h.md#bt_oof_root), [`rd_box_count`](include.render_doc.h.md#rd_box_count)

---

<a id="axis"></a>

### `axis`

`function` | [gui/browser_ui.c:5451](../../gui/browser_ui.c#L5451)

```c
* differs: items stack on the vertical main axis (fx_column_place) and align on * the horizontal cross axis (fx_cross_offset). spec/flex_layout.md, tanda 40. */ int is_col = !is_grid && (cdv.direction
```

**Returns:** `* differs: items stack on the vertical main`

---

<a id="slot"></a>

### `slot`

`function` | [gui/browser_ui.c:5504](../../gui/browser_ui.c#L5504)

```c
* layout slot (item 0 → rightmost, last item → leftmost). */ if (use_flex && cdv.direction ==...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `rightmost` | `item 0 →` |  |  |
| `leftmost` | `last item →` |  |  |

**Returns:** `* layout`

---

<a id="struct"></a>

### `struct`

`function` | [gui/browser_ui.c:5620](../../gui/browser_ui.c#L5620)

```c
* struct (0 = auto);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `0` |  | `auto` |  |

**Returns:** `*`

---

<a id="path"></a>

### `path`

`function` | [gui/browser_ui.c:5634](../../gui/browser_ui.c#L5634)

```c
* * Only a SYNTHESISED table grid takes this path (cdv.is_table), and only when ...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `is_table` | `cdv.` |  |  |

**Returns:** `* * Only a SYNTHESISED table grid takes this`

*Calls:* [`rd_at`](include.render_doc.h.md#rd_at)

---

<a id="own"></a>

### `own`

`function` | [gui/browser_ui.c:5890](../../gui/browser_ui.c#L5890)

```c
* root box of its own (rb < 0) the walk must still stop at the * container's box, or it re-opens the container (and its ancestors) * INSIDE the item -- which is what painted a nested nav's own backdro
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `rb` |  |  |  |

**Returns:** `* root box of its`

---

<a id="items"></a>

### `items`

`function` | [gui/browser_ui.c:5952](../../gui/browser_ui.c#L5952)

```c
* items (Flexbox 4.2);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `Flexbox` |  |  |  |

**Returns:** `*`

---

<a id="children"></a>

### `children`

`function` | [gui/browser_ui.c:6249](../../gui/browser_ui.c#L6249)

```c
* own content rect onto the stack so its children (text or nested boxes) place inside * it. At t...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `boxes` | `text or nested` |  |  |

**Returns:** `* own content rect onto the stack so its`

*Called by:* [`BT_MAUTO_RIGHT`](include.box_tree.h.md#bt_mauto_right)

---

<a id="behind"></a>

### `behind`

`function` | [gui/browser_ui.c:6258](../../gui/browser_ui.c#L6258)

```c
* previous block left behind (CSS 2.1 8.3.1) -- read from the element's cascade, * never a theme constant. The old code used th->paragraph_gap as a floor here, * which gave a <div> the vertical rhythm
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `CSS` |  |  |  |

**Returns:** `* previous block left`

---

<a id="column"></a>

### `column`

`function` | [gui/browser_ui.c:6457](../../gui/browser_ui.c#L6457)

```c
* * Returns the height of the tallest column (0 when there is nothing to fragment). */ static do...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fragment` | `0 when there is nothing to` |  |  |

**Returns:** `* * Returns the height of the tallest`

---

<a id="columns"></a>

### `columns`

`function` | [gui/browser_ui.c:6565](../../gui/browser_ui.c#L6565)

```c
* each card made 1080px columns (huggingface, github). */ static int deepest_open_on_path(const r...
```

**Returns:** `* each card made 1080px`

*Called by:* [`BT_MAUTO_RIGHT`](include.box_tree.h.md#bt_mauto_right)

---

<a id="treatment"></a>

### `treatment`

`function` | [gui/browser_ui.c:6651](../../gui/browser_ui.c#L6651)

```c
* block treatment (shrink-wrapped and placed by text-align), which is what a * standalon...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `align` | `shrink-wrapped and placed by text-` |  |  |

**Returns:** `* block`

---

<a id="context"></a>

### `context`

`function` | [gui/browser_ui.c:6779](../../gui/browser_ui.c#L6779)

```c
* side by side inside the current box context (spec/float.md). Blocks are grouped by * float_id into items (document order);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `md` | `spec/float.` |  |  |

**Returns:** `* side by side inside the current box`

---

<a id="x"></a>

### `x`

`function` | [gui/browser_ui.c:7064](../../gui/browser_ui.c#L7064)

```c
* reported x is already the BORDER x (the §7c.2 rule);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `rule` | `the §7c.2` |  |  |

**Returns:** `* reported`

---

<a id="thumbnail"></a>

### `thumbnail`

`function` | [gui/browser_ui.c:7315](../../gui/browser_ui.c#L7315)

```c
* is what made a wikipedia thumbnail (a 250px image and its caption, no * declared width) sp...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `caption` | `a 250px image and its` |  |  |
| `width` | `no * declared` |  |  |

**Returns:** `* is what made a wikipedia`

---

<a id="yet"></a>

### `yet`

`function` | [gui/browser_ui.c:7597](../../gui/browser_ui.c#L7597)

```c
* does not carry yet (WPT flex-abspos-staticpos-*). */ static int runs_share_float(const rd_doc *...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `staticpos` | `WPT flex-abspos- -*` |  |  |

**Returns:** `* does not carry`

---

<a id="chain"></a>

### `chain`

`function` | [gui/browser_ui.c:7658](../../gui/browser_ui.c#L7658)

```c
* chain (the box that left the normal flow at this pen position);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `position` | `the box that left the normal flow at this pen` |  |  |

**Returns:** `*`

---

<a id="anchor"></a>

### `anchor`

`function` | [gui/browser_ui.c:7750](../../gui/browser_ui.c#L7750)

```c
* anchor (spec/float.md §7d.3) exactly like a text block. An * empty/hidden one leaves cur_top untouched, so this is a no-op * for it. Without this a flex header never anchored and pulled * columns te
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `d` | `spec/float.md §7 .3` |  |  |

**Returns:** `*`

---

<a id="key"></a>

### `key`

`function` | [gui/browser_ui.c:7810](../../gui/browser_ui.c#L7810)

```c
* founders splits by key (stories, rail, footer nav each take * their column);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `column` | `footer nav each take * their` |  |  |

**Returns:** `* founders splits by`

---

<a id="have"></a>

### `have`

`function` | [gui/browser_ui.c:7824](../../gui/browser_ui.c#L7824)

```c
* as they always have (spec/float.md §6b.3). The line still open beside * the previous float is committed first, at its own top. */ flush_line(L, &s, th);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `spec/float.md §6 .3` |  |  |

**Returns:** `* as they always`

---

<a id="standalone"></a>

### `standalone`

`function` | [gui/browser_ui.c:7845](../../gui/browser_ui.c#L7845)

```c
* must not be treated as standalone (which would flush that line and give * the element a row of its own -- R7). */ size_t line_mate = replaced_opens_inline_line(doc, i);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `R7` | `which would flush that line and give * the element a row of its own --` |  |  |

**Returns:** `* must not be treated as`

---

<a id="it"></a>

### `it`

`function` | [gui/browser_ui.c:7905](../../gui/browser_ui.c#L7905)

```c
* column: flush first so the column lands above it (source order), * then move the anchor — the image bottom is the container top * for whatever follows. */ defer_flush(cr, w, L, &s, th, content_w, do
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `order` | `source` |  |  |

**Returns:** `* column: flush first so the column lands above`

---

<a id="count"></a>

### `count`

`function` | [gui/browser_ui.c:8001](../../gui/browser_ui.c#L8001)

```c
* the box count (a hostile parent cycle terminates). */ static int oof_depth(const rd_doc *doc, s...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `terminates` | `a hostile parent cycle` |  |  |

**Returns:** `* the box`

---

<a id="approximation"></a>

### `approximation`

`function` | [gui/browser_ui.c:8020](../../gui/browser_ui.c#L8020)

```c
* anchors on the Stage 2d approximation (fail-open: content never vanishes). */ static void oof_s...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vanishes` | `fail-open: content never` |  |  |

**Returns:** `* anchors on the Stage 2d`

---

<a id="margin"></a>

### `margin`

`function` | [gui/browser_ui.c:8156](../../gui/browser_ui.c#L8156)

```c
* own left margin (the margin box starts at the anchor point), a right- * anchored one ends at it. Same for the vertical axis. */ int right_anchored = (bd->inset_left == PV_LEN_UNSET || bd->inset_left
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `point` | `the margin box starts at the anchor` |  |  |

**Returns:** `* own left`

*Called by:* [`RC_FLOAT_FIT_MIN`](#rc_float_fit_min)

---

<a id="rd_build"></a>

### `rd_build`

`function` | [gui/browser_ui.c:8780](../../gui/browser_ui.c#L8780)

```c
* rd_build (-1 = auto/off -> theme caret). */ if (b->caret_color >= 0 && !w->force_theme) set_rgb(cr, rgb_from_packed(b->caret_color));
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `-1` |  | `auto/off -> theme caret` |  |

**Returns:** `*`

---

<a id="dies"></a>

### `dies`

`function` | [gui/browser_ui.c:9006](../../gui/browser_ui.c#L9006)

```c
* child dies (exec failed, device busy, daemon absent) is detected on the * next PCM write (EPIP...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `failed` | `exec` |  |  |
| `busy` | `device` |  |  |
| `absent` | `daemon` |  |  |

**Returns:** `* child`

---

<a id="descriptors"></a>

### `descriptors`

`function` | [gui/browser_ui.c:9029](../../gui/browser_ui.c#L9029)

```c
* descriptors (especially the Wayland display fd) so the sink does * not corrupt the Wayland protocol connection — the most common * cause of the "page flashes white and render loops" bug. */ close(p[
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `especially the Wayland display` |  |  |

**Returns:** `*`

---

<a id="again"></a>

### `again`

`function` | [gui/browser_ui.c:9110](../../gui/browser_ui.c#L9110)

```c
* before a respawn opens it again (the WNOHANG reap left the old * process alive long enough to make the new one fail with "Device * or resource busy"). Death is immediate, so the wait is too. */ kill
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `busy` | `the WNOHANG reap left the old * process alive long enough to make the new one fail with "Device * or resource "` |  |  |

**Returns:** `* before a respawn opens it`

---

<a id="blocking"></a>

### `blocking`

`function` | [gui/browser_ui.c:9397](../../gui/browser_ui.c#L9397)

```c
* are blocking (POLLIN guaranteed data is available). */ int flags = fcntl(out_fd, F_GETFL, 0);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `available` | `POLLIN guaranteed data is` |  |  |

**Returns:** `* are`

---

<a id="video_stop"></a>

### `video_stop`

`function` | [gui/browser_ui.c:9418](../../gui/browser_ui.c#L9418)

```c
* each segment loop so a video_stop() in the main thread (which sets it to 0 * then calls pthrea...
```

**Returns:** `* each segment loop so a`

---

<a id="upstream"></a>

### `upstream`

`function` | [gui/browser_ui.c:9624](../../gui/browser_ui.c#L9624)

```c
* upstream (see spec/css.md). */ static void box_path4(cairo_t *cr, double x, double y, double w,...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `md` | `see spec/css.` |  |  |

**Returns:** `*`

---

<a id="rect"></a>

### `rect`

`function` | [gui/browser_ui.c:9667](../../gui/browser_ui.c#L9667)

```c
* across rect (x,y,w,h): the gradient line runs through the rect center, long * enough that the first/last stops land on the corners. Stops at explicit * 0-1000 positions (pos1000, -1 or NULL = evenly
```

**Returns:** `the gradient line runs through the rect center, long * enough that the first/last stops land on the corners. Stops at explicit * 0-1000 positions (pos1000, -1 or NULL`

*Called by:* [`property`](src.css.c.md#property)

---

<a id="text"></a>

### `text`

`function` | [gui/browser_ui.c:9671](../../gui/browser_ui.c#L9671)

```c
* fill and gradient text (2026-07-19). */ static cairo_pattern_t *bui_linear_grad(double x, doubl...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `2026-07-19` |  |  |  |

**Returns:** `* fill and gradient`

---

<a id="spaced"></a>

### `spaced`

`function` | [gui/browser_ui.c:9746](../../gui/browser_ui.c#L9746)

```c
* or evenly spaced (bui_grad_color_at). */ static void bui_paint_conic(cairo_t *cr, double x, dou...
```

**Returns:** `* or evenly`

---

<a id="layer"></a>

### `layer`

`function` | [gui/browser_ui.c:9940](../../gui/browser_ui.c#L9940)

```c
* first layer (CSS multi-background: the first declared URL is the topmost) * and OVER bg_rgb/gradient, UNDER the border. Same sizing/repeat/position * as the first layer, using the SAME rc_box fields
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `topmost` | `CSS multi-background: the first declared URL is the` |  |  |

**Returns:** `* first`

---

<a id="cairo_set_dash"></a>

### `cairo_set_dash`

`function` | [gui/browser_ui.c:9990](../../gui/browser_ui.c#L9990)

```c
cairo_set_dash(cr, (double[])
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `double` |  |  |  |

---

<a id="cairo_set_dash"></a>

### `cairo_set_dash`

`function` | [gui/browser_ui.c:9993](../../gui/browser_ui.c#L9993)

```c
cairo_set_dash(cr, (double[])
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `double` |  |  |  |

---

<a id="cairo_set_dash"></a>

### `cairo_set_dash`

`function` | [gui/browser_ui.c:10033](../../gui/browser_ui.c#L10033)

```c
cairo_set_dash(cr, (double[])
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `double` |  |  |  |

---

<a id="cairo_set_dash"></a>

### `cairo_set_dash`

`function` | [gui/browser_ui.c:10036](../../gui/browser_ui.c#L10036)

```c
cairo_set_dash(cr, (double[])
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `double` |  |  |  |

---

<a id="convention"></a>

### `convention`

`function` | [gui/browser_ui.c:10056](../../gui/browser_ui.c#L10056)

```c
* on the 3D bevel convention (light top/left, dark right/bottom). */ int is_3d = (style == CSS_BST_GROOVE || style == CSS_BST_RIDGE || style == CSS_BST_INSET || style == CSS_BST_OUTSET);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `left` | `light top/` |  |  |
| `bottom` | `dark right/` |  |  |

**Returns:** `* on the 3D bevel`

---

<a id="set_rgb"></a>

### `set_rgb`

`function` | [gui/browser_ui.c:10070](../../gui/browser_ui.c#L10070)

```c
set_rgb(cr, (ui_rgb)
```

0xRRGGBB author colour -> theme RGB

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ui_rgb` |  |  |  |

> **Inherited:** Documentation from [`set_rgb`](#set_rgb) (gui/browser_ui_internal.h:106).

---

<a id="cairo_set_dash"></a>

### `cairo_set_dash`

`function` | [gui/browser_ui.c:10094](../../gui/browser_ui.c#L10094)

```c
cairo_set_dash(cr, (double[])
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `double` |  |  |  |

---

<a id="cairo_set_dash"></a>

### `cairo_set_dash`

`function` | [gui/browser_ui.c:10097](../../gui/browser_ui.c#L10097)

```c
cairo_set_dash(cr, (double[])
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `double` |  |  |  |

---

<a id="cairo_set_dash"></a>

### `cairo_set_dash`

`function` | [gui/browser_ui.c:10189](../../gui/browser_ui.c#L10189)

```c
cairo_set_dash(cr, (double[])
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `double` |  |  |  |

---

<a id="cairo_set_dash"></a>

### `cairo_set_dash`

`function` | [gui/browser_ui.c:10191](../../gui/browser_ui.c#L10191)

```c
cairo_set_dash(cr, (double[])
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `double` |  |  |  |

---

<a id="bg"></a>

### `bg`

`function` | [gui/browser_ui.c:10310](../../gui/browser_ui.c#L10310)

```c
* its own DISTINCT bg (an inline span highlight) still paints. */ int own_bid = row_owner_block_id(L, r);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `highlight` | `an inline span` |  |  |

**Returns:** `* its own DISTINCT`

---

<a id="rows"></a>

### `rows`

`function` | [gui/browser_ui.c:10516](../../gui/browser_ui.c#L10516)

```c
* RC_IMAGE rows (see its declaration);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `declaration` | `see its` |  |  |

**Returns:** `* RC_IMAGE`

---

<a id="fragment"></a>

### `fragment`

`function` | [gui/browser_ui.c:10517](../../gui/browser_ui.c#L10517)

```c
* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using * blk->block_id alo...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `block_id` | `rc_frag.` |  |  |
| `time` | `stamped at flow_emit_frag` |  |  |

**Returns:** `* first`

*Called by:* [`LN_MAX_FRAGMENT`](include.link_nav.h.md#ln_max_fragment)

---

<a id="the"></a>

### `the`

`function` | [gui/browser_ui.c:11088](../../gui/browser_ui.c#L11088)

```c
* the (already filtered) group with the shadow color, blur it, and * paint it under the group at the declared offset -- the shadow * follows the real content shape (PNG transparency, glyphs), not * th
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `filtered` | `already` |  |  |

**Returns:** `*`

---

<a id="limits"></a>

### `limits`

`function` | [gui/browser_ui.c:11166](../../gui/browser_ui.c#L11166)

```c
* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box * grouped this w...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `hidden` | `no overflow:` |  |  |
| `index` | `no negative z-` |  |  |

**Returns:** `* documents narrower v1`

---

<a id="fill"></a>

### `fill`

`function` | [gui/browser_ui.c:11264](../../gui/browser_ui.c#L11264)

```c
* fill (paint_content_row's r->bg_rgb branch) cascades the SAME author * background-color as the box, but paints in the caller's separate row pass -- * left ungrouped, it shows as a solid, un-faded re
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `branch` | `paint_content_row's r->bg_rgb` |  |  |

**Returns:** `*`

---

<a id="compositing"></a>

### `compositing`

`function` | [gui/browser_ui.c:11357](../../gui/browser_ui.c#L11357)

```c
* * Group compositing (M1.1 increments 3-4): a box that forms a CSS stacking context * (box_forms_stacking_context: opacity<1, mix-blend != normal, isolation:isolate, * transform != none, or the posit
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `increments` | `M1.1 3-4` |  |  |

**Returns:** `a box that forms a CSS stacking context * (box_forms_stacking_context: opacity<1, mix-blend !`

---

<a id="box"></a>

### `box`

`function` | [gui/browser_ui.c:11520](../../gui/browser_ui.c#L11520)

```c
* content belongs to that box (painted by its own positioned entry). */ if (sub == NULL)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `entry` | `painted by its own positioned` |  |  |

**Returns:** `* content belongs to that`

---

<a id="caller"></a>

### `caller`

`function` | [gui/browser_ui.c:12261](../../gui/browser_ui.c#L12261)

```c
* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the * out_path ve...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pdf` | `freedom.c --download-` |  |  |

**Returns:** `*`

---

<a id="ui_render_png"></a>

### `ui_render_png`

`function` | [gui/browser_ui.c:12284](../../gui/browser_ui.c#L12284)

```c
ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)
```

Headless PNG export (no Wayland; see include/ui.h).

One full-height bitmap of the whole page, the cheapest artifact for visual review (no PDF rasterise step). Same zeroed-window setup as ui_render_pdf.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `doc` | `rd_doc *` |  |  |
| `out_path` | `char *` |  |  |
| `out_h` | `long *` |  |  |

**Returns:** `ui_status`

---

<a id="origin"></a>

### `origin`

`function` | [gui/browser_ui.c:12340](../../gui/browser_ui.c#L12340)

```c
* top_url is the page origin (https or file://);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `file` | `https or ://` |  |  |

**Returns:** `* top_url is the page`

---

<a id="ui_render_png_images"></a>

### `ui_render_png_images`

`function` | [gui/browser_ui.c:12375](../../gui/browser_ui.c#L12375)

```c
ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url, tab_fetch_fn img_fetch, void *fetch_ctx, const char *out_path, long *out_h)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `doc` | `rd_doc *` |  |  |
| `t` | `tab *` |  |  |
| `top_url` | `char *` |  |  |
| `img_fetch` | `tab_fetch_fn` |  |  |
| `fetch_ctx` | `void *` |  |  |
| `out_path` | `char *` |  |  |
| `out_h` | `long *` |  |  |

**Returns:** `ui_status`

---

<a id="ui_render_pdf_images"></a>

### `ui_render_pdf_images`

`function` | [gui/browser_ui.c:12381](../../gui/browser_ui.c#L12381)

```c
ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url, tab_fetch_fn img_fetch, void *fetch_ctx, const char *out_path, long *out_pages)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `doc` | `rd_doc *` |  |  |
| `t` | `tab *` |  |  |
| `top_url` | `char *` |  |  |
| `img_fetch` | `tab_fetch_fn` |  |  |
| `fetch_ctx` | `void *` |  |  |
| `out_path` | `char *` |  |  |
| `out_pages` | `long *` |  |  |

**Returns:** `ui_status`

---

<a id="ui_dump_layout"></a>

### `ui_dump_layout`

`function` | [gui/browser_ui.c:12396](../../gui/browser_ui.c#L12396)

```c
ui_status ui_dump_layout(const rd_doc *doc)
```

Headless layout dump: runs the same layout_doc + position_doc pass as the on-screen/PNG renderer and prints the resolved box geometry (in-flow boxes and out-of-flow positioned boxes) to stdout as agent-readable text.

This is the layout-side counterpart to --dump-dom (which prints the pre-layout render tree): it makes the EFFECT of the layout engine verifiable without a display or a rasterised image (CI, an AI agent) — the Stacking/positioning bugs that a PNG would reveal are inspectable as plain numbers. See `--dump-layout` in spec/freedom.md. Pure I/O on already-resolved, already-fuzzed data; no socket, no file, no mutation of the doc.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `doc` | `rd_doc *` |  |  |

**Returns:** `ui_status`

---

<a id="in"></a>

### `in`

`function` | [gui/browser_ui.c:12418](../../gui/browser_ui.c#L12418)

```c
* a line landed in (Stage 3), which no other dump shows. Text stays out (it is * --dump-dom's job);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `Stage` |  |  |  |

**Returns:** `* a l`

---

<a id="firefox"></a>

### `Firefox`

`function` | [gui/browser_ui.c:12665](../../gui/browser_ui.c#L12665)

```c
* on its face does in Firefox (spec/page_view.md, tanda 40). */ static const rd_block *submit_pro...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `md` | `spec/page_view.` |  |  |
| `tanda` |  |  |  |

**Returns:** `* on its face does in`

---

<a id="reference"></a>

### `reference`

`function` | [gui/browser_ui.c:12738](../../gui/browser_ui.c#L12738)

```c
* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere: * hostile content...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `scheme` | `foreign` |  |  |
| `base` | `no resolvable` |  |  |

**Returns:** `*`

---

<a id="sf_ws_url_check"></a>

### `sf_ws_url_check`

`function` | [gui/browser_ui.c:12790](../../gui/browser_ui.c#L12790)

```c
&& sf_ws_url_check(op->data) == SF_OK && rp_host_of(op->data, host, sizeof host) == 0 && hb_check(w->hosts, host) != HB_BLOCK);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `op->` |  |  |

**Returns:** `&&`

---

<a id="memory"></a>

### `memory`

`function` | [gui/browser_ui.c:12912](../../gui/browser_ui.c#L12912)

```c
* memory (the href pointer, not its contents, was all the old code preserved). */ static void dis...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pointer` | `the href` |  |  |
| `contents` | `not its` |  |  |
| `preserved` | `was all the old code` |  |  |

**Returns:** `*`

---

<a id="get"></a>

### `GET`

`function` | [gui/browser_ui.c:12995](../../gui/browser_ui.c#L12995)

```c
* the network under weaker rules than a GET (Zero Trust). */ static void do_submit_post(browser_w...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `Trust` | `Zero` |  |  |

**Returns:** `* the network under weaker rules than a`

---

<a id="presentation"></a>

### `presentation`

`function` | [gui/browser_ui.c:13270](../../gui/browser_ui.c#L13270)

```c
* affect presentation (a repaint, which re-runs layout, suffices);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `repaint` | `a` |  |  |
| `layout` | `which re-runs` |  |  |

**Returns:** `* affect`

---

<a id="resizes"></a>

### `resizes`

`function` | [gui/browser_ui.c:13972](../../gui/browser_ui.c#L13972)

```c
* when the window resizes (a no-op for the other modes). */ if (w->reader) apply_theme(w);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `modes` | `a no-op for the other` |  |  |

**Returns:** `* when the window`

---

<a id="wl_array_for_each"></a>

### `wl_array_for_each`

`function` | [gui/browser_ui.c:13980](../../gui/browser_ui.c#L13980)

```c
wl_array_for_each(st, states)
```

---

<a id="element"></a>

### `element`

`function` | [gui/browser_ui.c:14037](../../gui/browser_ui.c#L14037)

```c
* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand * even without...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `div` | `a JS-driven button/` |  |  |
| `a` | `not just an < >` |  |  |

**Returns:** `* cursor:pointer`

---

<a id="down"></a>

### `down`

`function` | [gui/browser_ui.c:14641](../../gui/browser_ui.c#L14641)

```c
* defined further down (after dispatch_js_event) but called from ptr_enter/leave * /motion too. */ static void dispatch_mouse_event(browser_window *w, dom_node_id node_id, const char *event_type, int
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dispatch_js_event` | `after` |  |  |

**Returns:** `* defined further`

---

<a id="loop"></a>

### `loop`

`function` | [gui/browser_ui.c:15219](../../gui/browser_ui.c#L15219)

```c
* we return to the event loop (without this, the clipboard offer stays queued * and a paste that follows immediately might miss it). */ wl_display_roundtrip(w->display);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `this` | `without` |  |  |
| `it` | `the clipboard offer stays queued * and a paste that follows immediately might miss` |  |  |

**Returns:** `* we return to the event`

---

<a id="ui_run_browser"></a>

### `ui_run_browser`

`function` | [gui/browser_ui.c:15985](../../gui/browser_ui.c#L15985)

```c
ui_status ui_run_browser(const char *start_url)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `start_url` | `char *` |  |  |

**Returns:** `ui_status`

*Called by:* [`main`](src.freedom.c.md#main)

---

<a id="saving"></a>

### `saving`

`function` | [gui/browser_ui.c:16000](../../gui/browser_ui.c#L16000)

```c
* disables saving (never clobber);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `clobber` | `never` |  |  |

**Returns:** `* disables`

---

<a id="redraws"></a>

### `redraws`

`function` | [gui/browser_ui.c:16079](../../gui/browser_ui.c#L16079)

```c
* so a large page with frequent redraws (spinner, JS ticks, video frames) * never hits "Data too big for buffer". A 4 KiB buffer overflows when * accumulated messages exceed that, since manual flushes
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ticks` | `JS` |  |  |
| `frames` | `video` |  |  |

**Returns:** `* so a large page with frequent`

---

<a id="applies"></a>

### `applies`

`function` | [gui/browser_ui.c:16149](../../gui/browser_ui.c#L16149)

```c
* persisted choice applies (prefs_parse already clamped it to a valid mode). */ const char *js_env = getenv("FREEDOM_JS");
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `mode` | `prefs_parse already clamped it to a valid` |  |  |

**Returns:** `* persisted choice`

---

<a id="flow"></a>

### `flow`

`function` | [gui/browser_ui.c:16358](../../gui/browser_ui.c#L16358)

```c
* flow (counting them starved aplay). A video frame read while * overdue overwrites the held slot (standard player frame drop);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `aplay` | `counting them starved` |  |  |

**Returns:** `*`

---

<a id="cost"></a>

### `cost`

`function` | [gui/browser_ui.c:16380](../../gui/browser_ui.c#L16380)

```c
* measured cost (floor 33 ms = the existing ~30 fps ceiling): * cheap pages paint at...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ms` | `floor 33` | `the existing ~30 fps ceiling` |  |

**Returns:** `* cheap pages paint at...`

---

## Macros

<a id="_gnu_source"></a>

### `_GNU_SOURCE`

`macro` | [gui/browser_ui.c:12](../../gui/browser_ui.c#L12)

```c
#define _GNU_SOURCE
```

---

<a id="ui_tab_min_w"></a>

### `UI_TAB_MIN_W`

`macro` | [gui/browser_ui.c:86](../../gui/browser_ui.c#L86)

```c
#define UI_TAB_MIN_W
```

height of the tab strip (between titlebar and toolbar)

---

<a id="ui_tab_max_w"></a>

### `UI_TAB_MAX_W`

`macro` | [gui/browser_ui.c:87](../../gui/browser_ui.c#L87)

```c
#define UI_TAB_MAX_W
```

minimum drawn width of a tab before it shrinks further

---

<a id="ui_tab_new_w"></a>

### `UI_TAB_NEW_W`

`macro` | [gui/browser_ui.c:88](../../gui/browser_ui.c#L88)

```c
#define UI_TAB_NEW_W
```

preferred width of a tab when there is room

---

<a id="ui_tab_close_w"></a>

### `UI_TAB_CLOSE_W`

`macro` | [gui/browser_ui.c:89](../../gui/browser_ui.c#L89)

```c
#define UI_TAB_CLOSE_W
```

width of the trailing "new tab" (+) button

---

<a id="ui_btn_w"></a>

### `UI_BTN_W`

`macro` | [gui/browser_ui.c:90](../../gui/browser_ui.c#L90)

```c
#define UI_BTN_W
```

width of a tab's close (x) hot zone at its right edge

---

<a id="ui_win_btn_w"></a>

### `UI_WIN_BTN_W`

`macro` | [gui/browser_ui.c:91](../../gui/browser_ui.c#L91)

```c
#define UI_WIN_BTN_W
```

---

<a id="ui_margin"></a>

### `UI_MARGIN`

`macro` | [gui/browser_ui.c:92](../../gui/browser_ui.c#L92)

```c
#define UI_MARGIN
```

---

<a id="ui_btn_left"></a>

### `UI_BTN_LEFT`

`macro` | [gui/browser_ui.c:93](../../gui/browser_ui.c#L93)

```c
#define UI_BTN_LEFT
```

---

<a id="ui_list_indent"></a>

### `UI_LIST_INDENT`

`macro` | [gui/browser_ui.c:97](../../gui/browser_ui.c#L97)

```c
#define UI_LIST_INDENT
```

Left indent (px) per UA-padded list level: the HTML UA sheet gives ul/ol `padding-inline-start: 40px` (HTML rendering 15.3.7).

A level whose padding the author declared does not count (page_view), its padding goes through the box model.

---

<a id="ui_scrollbar_w"></a>

### `UI_SCROLLBAR_W`

`macro` | [gui/browser_ui.c:102](../../gui/browser_ui.c#L102)

```c
#define UI_SCROLLBAR_W
```

Vertical scrollbar in the content area's right gutter.

The gutter width is always reserved (subtracted from the content width) so the scroll affordance and the click hit-test share one geometry and never overlap the text.

---

<a id="ui_scrollbar_min"></a>

### `UI_SCROLLBAR_MIN`

`macro` | [gui/browser_ui.c:103](../../gui/browser_ui.c#L103)

```c
#define UI_SCROLLBAR_MIN
```

reserved gutter width on the content's right edge

---

<a id="ui_scrollbar_pad"></a>

### `UI_SCROLLBAR_PAD`

`macro` | [gui/browser_ui.c:104](../../gui/browser_ui.c#L104)

```c
#define UI_SCROLLBAR_PAD
```

minimum thumb height so it stays grabbable

---

<a id="ui_resize_margin"></a>

### `UI_RESIZE_MARGIN`

`macro` | [gui/browser_ui.c:108](../../gui/browser_ui.c#L108)

```c
#define UI_RESIZE_MARGIN
```

Border band (px) that starts an interactive window resize when dragged, used only with client-side decorations (the compositor handles edges under SSD).

---

<a id="ui_menu_w"></a>

### `UI_MENU_W`

`macro` | [gui/browser_ui.c:113](../../gui/browser_ui.c#L113)

```c
#define UI_MENU_W
```

Options menu (gear) panel geometry and the pointer cursor size, gathered with the other chrome constants so no value is hardcoded at a call site.

The panel is wide enough to edit a User-Agent string.

---

<a id="ui_menu_pad"></a>

### `UI_MENU_PAD`

`macro` | [gui/browser_ui.c:115](../../gui/browser_ui.c#L115)

```c
#define UI_MENU_PAD
```

---

<a id="ui_check_sz"></a>

### `UI_CHECK_SZ`

`macro` | [gui/browser_ui.c:116](../../gui/browser_ui.c#L116)

```c
#define UI_CHECK_SZ
```

---

<a id="ui_hamburger_w"></a>

### `UI_HAMBURGER_W`

`macro` | [gui/browser_ui.c:119](../../gui/browser_ui.c#L119)

```c
#define UI_HAMBURGER_W
```

height of the editable User-Agent box

---

<a id="ui_hamburger_gap"></a>

### `UI_HAMBURGER_GAP`

`macro` | [gui/browser_ui.c:120](../../gui/browser_ui.c#L120)

```c
#define UI_HAMBURGER_GAP
```

width of the drawn menu-button icon

---

<a id="ui_cursor_size"></a>

### `UI_CURSOR_SIZE`

`macro` | [gui/browser_ui.c:121](../../gui/browser_ui.c#L121)

```c
#define UI_CURSOR_SIZE
```

vertical gap between the three icon bars

---

<a id="ui_toast_pad"></a>

### `UI_TOAST_PAD`

`macro` | [gui/browser_ui.c:122](../../gui/browser_ui.c#L122)

```c
#define UI_TOAST_PAD
```

themed cursor size in px (XCURSOR_SIZE default)

---

<a id="omni_max_sugg"></a>

### `OMNI_MAX_SUGG`

`macro` | [gui/browser_ui.c:123](../../gui/browser_ui.c#L123)

```c
#define OMNI_MAX_SUGG
```

padding inside the toast banner

---

<a id="ui_two_pi"></a>

### `UI_TWO_PI`

`macro` | [gui/browser_ui.c:125](../../gui/browser_ui.c#L125)

```c
#define UI_TWO_PI
```

height of one omnibox suggestion row

---

<a id="ui_input_pad"></a>

### `UI_INPUT_PAD`

`macro` | [gui/browser_ui.c:129](../../gui/browser_ui.c#L129)

```c
#define UI_INPUT_PAD
```

Form control geometry: inner padding of a text box, the preferred text-box width (clamped to the content width), and the horizontal padding of a button.

---

<a id="ui_input_measure_w"></a>

### `UI_INPUT_MEASURE_W`

`macro` | [gui/browser_ui.c:132](../../gui/browser_ui.c#L132)

```c
#define UI_INPUT_MEASURE_W
```

Conventional main-axis width a form control reserves as a flex item until a real intrinsic-width model lands (roadmap R11).

Roughly a browser's default text input.

---

<a id="ui_input_width"></a>

### `UI_INPUT_WIDTH`

`macro` | [gui/browser_ui.c:133](../../gui/browser_ui.c#L133)

```c
#define UI_INPUT_WIDTH
```

---

<a id="ui_button_hpad"></a>

### `UI_BUTTON_HPAD`

`macro` | [gui/browser_ui.c:134](../../gui/browser_ui.c#L134)

```c
#define UI_BUTTON_HPAD
```

---

<a id="ui_form_fields_max"></a>

### `UI_FORM_FIELDS_MAX`

`macro` | [gui/browser_ui.c:135](../../gui/browser_ui.c#L135)

```c
#define UI_FORM_FIELDS_MAX
```

---

<a id="ui_underline_offset"></a>

### `UI_UNDERLINE_OFFSET`

`macro` | [gui/browser_ui.c:140](../../gui/browser_ui.c#L140)

```c
#define UI_UNDERLINE_OFFSET
```

Link/author text-decoration geometry, expressed relative to the run's font so it scales with heading-sized text.

Underline offset is below the baseline; the line-through sits over the x-height and the overline above the ascent.

---

<a id="ui_underline_thick"></a>

### `UI_UNDERLINE_THICK`

`macro` | [gui/browser_ui.c:141](../../gui/browser_ui.c#L141)

```c
#define UI_UNDERLINE_THICK
```

---

<a id="ui_strike_offset"></a>

### `UI_STRIKE_OFFSET`

`macro` | [gui/browser_ui.c:142](../../gui/browser_ui.c#L142)

```c
#define UI_STRIKE_OFFSET
```

---

<a id="ui_overline_offset"></a>

### `UI_OVERLINE_OFFSET`

`macro` | [gui/browser_ui.c:143](../../gui/browser_ui.c#L143)

```c
#define UI_OVERLINE_OFFSET
```

above the baseline (≈ through the x-height)

---

<a id="ui_slice_max"></a>

### `UI_SLICE_MAX`

`macro` | [gui/browser_ui.c:147](../../gui/browser_ui.c#L147)

```c
#define UI_SLICE_MAX
```

Largest text slice measured/drawn at once (one word, or one clipped label).

Words longer than this are still placed, just measured up to the cap.

---

<a id="ui_menu_count"></a>

### `UI_MENU_COUNT`

`macro` | [gui/browser_ui.c:206](../../gui/browser_ui.c#L206)

```c
#define UI_MENU_COUNT
```

---

<a id="ui_image_max_body"></a>

### `UI_IMAGE_MAX_BODY`

`macro` | [gui/browser_ui.c:224](../../gui/browser_ui.c#L224)

```c
#define UI_IMAGE_MAX_BODY
```

Hard cap on the response body of an image subresource (a PNG/JPEG; the decoder bounds the decoded pixels further).

Keeps a hostile server from streaming forever.

---

<a id="ui_max_tabs"></a>

### `UI_MAX_TABS`

`macro` | [gui/browser_ui.c:263](../../gui/browser_ui.c#L263)

```c
#define UI_MAX_TABS
```

Maximum concurrent tabs.

Bounded so the per-tab snapshot array is a fixed, auditable size (no unbounded growth from a hostile page opening tabs; this browser never opens a tab on a page's behalf anyway).

*Calls:* [`NULL`](src.css.c.md#null)

---

<a id="ui_reader_column_w"></a>

### `UI_READER_COLUMN_W`

`macro` | [gui/browser_ui.c:582](../../gui/browser_ui.c#L582)

```c
#define UI_READER_COLUMN_W
```

Comfortable reading-column width (px) used by distraction-free mode: the text is centered in a column no wider than this, so long lines do not sprawl edge to edge.

*Calls:* [`ui_theme_for`](gui.bui_theme.c.md#ui_theme_for), [`zm_apply`](include.zoom.h.md#zm_apply), [`zm_scale`](include.zoom.h.md#zm_scale)

---

<a id="font_stash_max_sheets"></a>

### `FONT_STASH_MAX_SHEETS`

`macro` | [gui/browser_ui.c:1467](../../gui/browser_ui.c#L1467)

```c
#define FONT_STASH_MAX_SHEETS
```

@font-face stash bounds (spec/webfont.md b3b, anti-DoS): at most 16 served sheets and 2 MiB retained per load.

Real pages name a handful of stylesheets; beyond the caps the pass still runs on what fit (fail-visible, never the page).

---

<a id="font_stash_max_bytes"></a>

### `FONT_STASH_MAX_BYTES`

`macro` | [gui/browser_ui.c:1468](../../gui/browser_ui.c#L1468)

```c
#define FONT_STASH_MAX_BYTES
```

*Calls:* [`free`](include.prefs.h.md#free)

---

<a id="js_nav_max"></a>

### `JS_NAV_MAX`

`macro` | [gui/browser_ui.c:2121](../../gui/browser_ui.c#L2121)

```c
#define JS_NAV_MAX
```

Cap on consecutive JS-driven navigations (location.href=) without a settling page, so a hostile redirect loop cannot pin the browser.

Reset when a page settles.

---

<a id="hist_step_depth_max"></a>

### `HIST_STEP_DEPTH_MAX`

`macro` | [gui/browser_ui.c:2123](../../gui/browser_ui.c#L2123)

```c
#define HIST_STEP_DEPTH_MAX
```

Nested history steps a page can chain (a popstate handler that calls back()).

---

<a id="js_ticks_per_load"></a>

### `JS_TICKS_PER_LOAD`

`macro` | [gui/browser_ui.c:2241](../../gui/browser_ui.c#L2241)

```c
#define JS_TICKS_PER_LOAD
```

Cap on OP_TICKs per page load (anti battery-drain; the shared per-page JS budget already bounds the total script time). ~240 ticks at the 16 ms floor is a few seconds of animation, plenty for progressive-render patterns.

---

<a id="ui_reload_x"></a>

### `UI_RELOAD_X`

`macro` | [gui/browser_ui.c:2990](../../gui/browser_ui.c#L2990)

```c
#define UI_RELOAD_X
```

The reload button sits as the third left chrome button (after back/forward), at a fixed x; callers that need it derive it here so the layout stays single-sourced.

---

<a id="rc_box_stack_max"></a>

### `RC_BOX_STACK_MAX`

`macro` | [gui/browser_ui.c:3308](../../gui/browser_ui.c#L3308)

```c
#define RC_BOX_STACK_MAX
```

Max box-nesting depth the painter composes (anti-DoS; deeper boxes are clamped to the innermost open box, so a pathological tree never overflows the stack).

---

<a id="rc_float_max"></a>

### `RC_FLOAT_MAX`

`macro` | [gui/browser_ui.c:3312](../../gui/browser_ui.c#L3312)

```c
#define RC_FLOAT_MAX
```

Live float exclusions one layout state tracks (anti-DoS).

A ninth float is dropped, so a pathological page overlaps a float instead of losing content.

---

<a id="rc_float_fit_min"></a>

### `RC_FLOAT_FIT_MIN`

`macro` | [gui/browser_ui.c:3319](../../gui/browser_ui.c#L3319)

```c
#define RC_FLOAT_FIT_MIN
```

Narrowest strip beside a float that still counts as room for a line box.

Below it the line is shifted under the float instead (CSS 2.1 9.5). It is a width in px, not a heuristic about content: a strip narrower than one average word cannot hold a line box, and pretending it can is what makes text paint on top of the float.

*Calls:* [`line`](#line), [`margin`](#margin), [`block`](src.box_tree.c.md#block)

---

<a id="flex_measure_w"></a>

### `FLEX_MEASURE_W`

`macro` | [gui/browser_ui.c:4908](../../gui/browser_ui.c#L4908)

```c
#define FLEX_MEASURE_W
```

Wrap threshold used when measuring an item's MAX-CONTENT width: wide enough that no realistic line wraps, small enough to stay far from any overflow in the accumulating pen arithmetic.

---

<a id="flex_min_measure_w"></a>

### `FLEX_MIN_MEASURE_W`

`macro` | [gui/browser_ui.c:4913](../../gui/browser_ui.c#L4913)

```c
#define FLEX_MIN_MEASURE_W
```

The other end of the same measuring stick: flowed this narrow, every legal break is taken, so the widest resulting line IS the item's MIN-CONTENT width (CSS Sizing 3 5.1).

Like FLEX_MEASURE_W it is a measurement device, not a layout value -- no rendered geometry is ever placed at this width.

---

<a id="rc_max_out_of_flow"></a>

### `RC_MAX_OUT_OF_FLOW`

`macro` | [gui/browser_ui.c:6706](../../gui/browser_ui.c#L6706)

```c
#define RC_MAX_OUT_OF_FLOW
```

Stage 2: positioned blocks (absolute/fixed) that were skipped from the in-flow pass are recorded here for position_doc to lay out afterwards.

The cap mirrors PV's per-page container cap; a hostile page cannot exceed it.

---

<a id="rc_defer_cols"></a>

### `RC_DEFER_COLS`

`macro` | [gui/browser_ui.c:6814](../../gui/browser_ui.c#L6814)

```c
#define RC_DEFER_COLS
```

Deferred pull-up float columns (spec/float.md §7d.2-7d.3).

A float band whose groups live inside an OUTER float founder (the rail's
inner poll section, the stories inside .main-wrap) cannot be placed by the
sequential band loop: its outer column never shares a band with the earlier
content it must sit beside. Such bands defer: their block ranges collect
into a column keyed by the outermost founder id, and the column is placed
(beside earlier content, at the tracked anchor) at the next in-flow,
non-deferred block or EOF. Everything is bounded static storage; every
overflow degrades to the old inline path (fail-open: content overlaps or
stacks instead of vanishing). With no nested float in the document the map
stays empty and every band lays out exactly as before.

---

<a id="rc_defer_ranges"></a>

### `RC_DEFER_RANGES`

`macro` | [gui/browser_ui.c:6815](../../gui/browser_ui.c#L6815)

```c
#define RC_DEFER_RANGES
```

---

<a id="rc_defer_band_runs"></a>

### `RC_DEFER_BAND_RUNS`

`macro` | [gui/browser_ui.c:6897](../../gui/browser_ui.c#L6897)

```c
#define RC_DEFER_BAND_RUNS
```

Partition band [start, end) by defer key (spec/float.md §7d.2): a real band carries several outer founders (stories under 6, the aside under 67, footer nav under 75/89, plus single-level floats like the fortune quote under their own id).

Appends each key's maximal runs to its deferred column and returns the number of distinct keys. Returns -1 (lay the whole band inline, today's path, fail-open) when the band has no nesting at all (no oid and no id naming an outer founder: the byte-identical fast path for ordinary float pages) or any bound would overflow. OOF blocks ride the run they sit in (grouping and flow skip them with the same predicate, so they break nothing).

---

<a id="bui_conic_slices"></a>

### `BUI_CONIC_SLICES`

`macro` | [gui/browser_ui.c:9740](../../gui/browser_ui.c#L9740)

```c
#define BUI_CONIC_SLICES
```

---

<a id="ov_max_depth"></a>

### `OV_MAX_DEPTH`

`macro` | [gui/browser_ui.c:10441](../../gui/browser_ui.c#L10441)

```c
#define OV_MAX_DEPTH
```

Max overflow:hidden nesting depth (anti-DoS).

---

<a id="h2r"></a>

### `H2R`

`macro` | [gui/browser_ui.c:11044](../../gui/browser_ui.c#L11044)

```c
#define H2R(p,q,t)
```

---

<a id="pdf_page_w"></a>

### `PDF_PAGE_W`

`macro` | [gui/browser_ui.c:11918](../../gui/browser_ui.c#L11918)

```c
#define PDF_PAGE_W
```

PDF page geometry: US Letter at 72 dpi (Cairo's PDF user-space unit is 1 point = 1/72 inch), with a uniform margin.

---

<a id="pdf_margin"></a>

### `PDF_MARGIN`

`macro` | [gui/browser_ui.c:11920](../../gui/browser_ui.c#L11920)

```c
#define PDF_MARGIN
```

---

<a id="png_page_w"></a>

### `PNG_PAGE_W`

`macro` | [gui/browser_ui.c:12082](../../gui/browser_ui.c#L12082)

```c
#define PNG_PAGE_W
```

PNG raster geometry: a single continuous bitmap (not paginated) of the whole page, sized to the laid-out content.

The width fixes the wrap column; the height follows the content but is capped so a hostile page cannot force an unbounded allocation (a taller page is clipped at PNG_MAX_H).

---

<a id="png_margin"></a>

### `PNG_MARGIN`

`macro` | [gui/browser_ui.c:12095](../../gui/browser_ui.c#L12095)

```c
#define PNG_MARGIN
```

Headless image padding.

0 by default: the PNG canvas IS the 1000px viewport, laid out edge to edge exactly like the reference renderer's headless screenshot (no scrollbar gutter, no window margins in either), so the two bitmaps share canvas AND content width 1:1 (spec/parity.md §4). A page can still opt into top whitespace via html_margin_top. Before, 24px here laid every headless page out 48px narrower than the reference at the same nominal width, and the absolute gap propagated down every inset chain (slashdot text 50px too narrow at every level once float columns started honouring boxes). Only the headless PNG/dump paths read this; the interactive window keeps its own margins + scrollbar gutter (content_width).

---

<a id="fbw_w"></a>

### `FBW_W`

`macro` | [gui/browser_ui.c:14073](../../gui/browser_ui.c#L14073)

```c
#define FBW_W
```

---

<a id="fbw_header"></a>

### `FBW_HEADER`

`macro` | [gui/browser_ui.c:14075](../../gui/browser_ui.c#L14075)

```c
#define FBW_HEADER
```

---

<a id="fbw_pad"></a>

### `FBW_PAD`

`macro` | [gui/browser_ui.c:14076](../../gui/browser_ui.c#L14076)

```c
#define FBW_PAD
```

---

<a id="fbw_line"></a>

### `FBW_LINE`

`macro` | [gui/browser_ui.c:14077](../../gui/browser_ui.c#L14077)

```c
#define FBW_LINE
```

---

<a id="fbw_gutter"></a>

### `FBW_GUTTER`

`macro` | [gui/browser_ui.c:14078](../../gui/browser_ui.c#L14078)

```c
#define FBW_GUTTER
```

---

<a id="fbw_min_split"></a>

### `FBW_MIN_SPLIT`

`macro` | [gui/browser_ui.c:14079](../../gui/browser_ui.c#L14079)

```c
#define FBW_MIN_SPLIT
```

---

<a id="fbw_max_split"></a>

### `FBW_MAX_SPLIT`

`macro` | [gui/browser_ui.c:14080](../../gui/browser_ui.c#L14080)

```c
#define FBW_MAX_SPLIT
```

---

<a id="fbw_copy_btn_w"></a>

### `FBW_COPY_BTN_W`

`macro` | [gui/browser_ui.c:14081](../../gui/browser_ui.c#L14081)

```c
#define FBW_COPY_BTN_W
```

---
