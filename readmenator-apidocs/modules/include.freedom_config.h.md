# `include/freedom_config.h`

> Source: [include/freedom_config.h:1](../../include/freedom_config.h#L1) | language `h` | coverage 92.3% | [API index](../index.md)

## Contents

- **Macros:** [`FC_PNG_PAGE_W`](#fc_png_page_w), [`FC_TRUSTED_JS_BUDGET_MS`](#fc_trusted_js_budget_ms), [`FC_PNG_MARGIN`](#fc_png_margin), [`FC_FLEX_MEASURE_W`](#fc_flex_measure_w), [`FC_FLEX_MIN_MEASURE_W`](#fc_flex_min_measure_w), [`FC_FONT_CHAIN_MAX`](#fc_font_chain_max), [`FC_MAX_BOXES`](#fc_max_boxes), [`FC_FONT_FALLBACK_PX`](#fc_font_fallback_px), [`FC_UI_FONT_SIZE`](#fc_ui_font_size), [`FC_MAX_AUTHOR_CSS_BYTES`](#fc_max_author_css_bytes), [`FC_LAZY_IMAGE_MARGIN_PX`](#fc_lazy_image_margin_px), [`FC_TAB_OP_NET_BUDGET_MS`](#fc_tab_op_net_budget_ms)

## Macros

<a id="fc_png_page_w"></a>

### `FC_PNG_PAGE_W`

`macro` | [include/freedom_config.h:20](../../include/freedom_config.h#L20)

```c
#define FC_PNG_PAGE_W
```

Width in px of the headless PNG export canvas (--download-png) and of the parity viewport.

The harness renders Firefox at this same width so both engines measure the SAME document; the normalised desktop identity (anti-fingerprint) stays 1920 and only this render viewport uses it.

---

<a id="fc_trusted_js_budget_ms"></a>

### `FC_TRUSTED_JS_BUDGET_MS`

`macro` | [include/freedom_config.h:29](../../include/freedom_config.h#L29)

```c
#define FC_TRUSTED_JS_BUDGET_MS
```

Page-wide script time budget (ms) for a TRUSTED page (allow.conf AND js.conf): a modern app (github's React bundle) needs well over the untrusted 1 s budget in an interpreter.

The user consented to this host; the per-task interrupt still applies.

---

<a id="fc_png_margin"></a>

### `FC_PNG_MARGIN`

`macro` | [include/freedom_config.h:33](../../include/freedom_config.h#L33)

```c
#define FC_PNG_MARGIN
```

Padding around the PNG export canvas (px): the document's content box is FC_PNG_PAGE_W minus twice this.

A page's own <html> margin overrides it.

---

<a id="fc_flex_measure_w"></a>

### `FC_FLEX_MEASURE_W`

`macro` | [include/freedom_config.h:44](../../include/freedom_config.h#L44)

```c
#define FC_FLEX_MEASURE_W
```

Wrap threshold in px used when measuring an item's MAX-CONTENT width: wide enough that no realistic line wraps, small enough to stay far from any overflow in the accumulating pen arithmetic.

A measurement device, not a layout value -- no rendered geometry is ever placed at this width.

---

<a id="fc_flex_min_measure_w"></a>

### `FC_FLEX_MIN_MEASURE_W`

`macro` | [include/freedom_config.h:50](../../include/freedom_config.h#L50)

```c
#define FC_FLEX_MIN_MEASURE_W
```

The other end of the same measuring stick (px): flowed this narrow, every legal break is taken, so the widest resulting line IS the item's MIN-CONTENT width (CSS Sizing 3 5.1).

Like FC_FLEX_MEASURE_W it is a measurement device, not a layout value.

---

<a id="fc_font_chain_max"></a>

### `FC_FONT_CHAIN_MAX`

`macro` | [include/freedom_config.h:55](../../include/freedom_config.h#L55)

```c
#define FC_FONT_CHAIN_MAX
```

Ceiling on the inherited font-size chain the renderer resolves per element.

The chain depth is chosen by the attacker, so this is an anti-DoS bound: the walk is iterative and capped here, never recursive.

---

<a id="fc_max_boxes"></a>

### `FC_MAX_BOXES`

`macro` | [include/freedom_config.h:60](../../include/freedom_config.h#L60)

```c
#define FC_MAX_BOXES
```

Ceiling on the per-page box registry.

Coupled to the out-of-flow resolver's indexed storage by _Static_assert in page_view.c -- a normal page can exceed a lower value, which is a render bug, not a DoS bound.

---

<a id="fc_font_fallback_px"></a>

### `FC_FONT_FALLBACK_PX`

`macro` | [include/freedom_config.h:65](../../include/freedom_config.h#L65)

```c
#define FC_FONT_FALLBACK_PX
```

Fallback font size in px when a text shape carries no resolved size.

Single source for the former scattered 16.0 literals in painters and harnesses; matches the UA root size so fallback text measures like body.

---

<a id="fc_ui_font_size"></a>

### `FC_UI_FONT_SIZE`

`macro` | [include/freedom_config.h:69](../../include/freedom_config.h#L69)

```c
#define FC_UI_FONT_SIZE
```

Chrome font size in px for the minimal Wayland UI shell.

Formerly duplicated as UI_FONT_SIZE in gui/ui_render.c and gui/browser_ui_internal.h.

---

<a id="fc_max_author_css_bytes"></a>

### `FC_MAX_AUTHOR_CSS_BYTES`

`macro` | [include/freedom_config.h:77](../../include/freedom_config.h#L77)

```c
#define FC_MAX_AUTHOR_CSS_BYTES
```

Ceiling on the author CSS text one page may feed the parser: the document's <style> blocks plus its fetched <link> sheets, together.

It is an anti-DoS bound on parser memory and time, and it must sit ABOVE what real pages ship: github.com's front page links ~2.4 MB of distinct CSS, and the former 1 MiB value was consumed by its four colour-theme sheets alone, so the layout sheets that follow them were dropped whole and the page rendered unstyled.

---

<a id="fc_lazy_image_margin_px"></a>

### `FC_LAZY_IMAGE_MARGIN_PX`

`macro` | [include/freedom_config.h:80](../../include/freedom_config.h#L80)

```c
#define FC_LAZY_IMAGE_MARGIN_PX
```

Distance (px) beyond the viewport at which a loading="lazy" image starts loading.

---

<a id="fc_tab_op_net_budget_ms"></a>

### `FC_TAB_OP_NET_BUDGET_MS`

`macro` | [include/freedom_config.h:86](../../include/freedom_config.h#L86)

```c
#define FC_TAB_OP_NET_BUDGET_MS
```

Wall time (ms) the trusted parent spends serving ONE worker operation's network requests after the page load (a timer, click or observer callback).

The fetch is synchronous in the GUI thread, so this bounds how long a slow server can freeze the window; once spent, the rest of that operation's requests fail (status 0) instead of blocking.

---
