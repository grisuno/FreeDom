# `include/freedom_config.h`

> Source: [include/freedom_config.h:1](../../include/freedom_config.h#L1) | language `h` | coverage 85.2% | [API index](../index.md)

## Contents

- **Macros:** [`FC_PNG_PAGE_W`](#fc_png_page_w), [`FC_MONO_DEFAULT_PX`](#fc_mono_default_px), [`FC_SMOOTH_SCROLL_MS`](#fc_smooth_scroll_ms), [`FC_SMOOTH_SCROLL_FRAME_MS`](#fc_smooth_scroll_frame_ms), [`FC_SMOOTH_SCROLL_ANCHOR_MS`](#fc_smooth_scroll_anchor_ms), [`FC_ANCHOR_HOLD_MS`](#fc_anchor_hold_ms), [`FC_JS_FRAGMENT_DEPTH`](#fc_js_fragment_depth), [`FC_TRUSTED_JS_BUDGET_MS`](#fc_trusted_js_budget_ms), [`FC_PNG_MARGIN`](#fc_png_margin), [`FC_FLEX_MEASURE_W`](#fc_flex_measure_w), [`FC_FLEX_MIN_MEASURE_W`](#fc_flex_min_measure_w), [`FC_FONT_CHAIN_MAX`](#fc_font_chain_max), [`FC_MAX_BOXES`](#fc_max_boxes), [`FC_FONT_FALLBACK_PX`](#fc_font_fallback_px), [`FC_UI_FONT_SIZE`](#fc_ui_font_size), [`FC_MAX_AUTHOR_CSS_BYTES`](#fc_max_author_css_bytes), [`FC_SHC_MAX_TEXT_BYTES`](#fc_shc_max_text_bytes), [`FC_SHC_MAX_QUERIES`](#fc_shc_max_queries), [`FC_MASK_CACHE_BYTES`](#fc_mask_cache_bytes), [`FC_MASK_CACHE_ENTRIES`](#fc_mask_cache_entries), [`FC_LAZY_IMAGE_MARGIN_PX`](#fc_lazy_image_margin_px), [`FC_TAB_OP_NET_BUDGET_MS`](#fc_tab_op_net_budget_ms), [`FC_NET_LOAD_SETTLE_MS`](#fc_net_load_settle_ms), [`FC_NET_POLL_MS`](#fc_net_poll_ms), [`FC_NET_TICK_SETTLE_MS`](#fc_net_tick_settle_ms), [`FC_TABLE_TRACK_MAX_PX`](#fc_table_track_max_px)

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

<a id="fc_mono_default_px"></a>

### `FC_MONO_DEFAULT_PX`

`macro` | [include/freedom_config.h:26](../../include/freedom_config.h#L26)

```c
#define FC_MONO_DEFAULT_PX
```

Default size of the bare generic `monospace` (code/kbd/samp/tt/pre), against 16 px for every other family.

Firefox's pref says 13 (font.size.monospace.x-western) but on Linux it computes 12 px (getComputedStyle, measured on the parity host, tanda 102): the reference renderer is what we match. spec/page_view.md "monospace genérica".

---

<a id="fc_smooth_scroll_ms"></a>

### `FC_SMOOTH_SCROLL_MS`

`macro` | [include/freedom_config.h:31](../../include/freedom_config.h#L31)

```c
#define FC_SMOOTH_SCROLL_MS
```

Animated page scroll (spec/smooth_scroll.md): duration of one wheel/key scroll, as Firefox's general.smoothScroll durations (~150 ms), and the loop's wake interval while one is in flight (the paint itself paces the frames).

---

<a id="fc_smooth_scroll_frame_ms"></a>

### `FC_SMOOTH_SCROLL_FRAME_MS`

`macro` | [include/freedom_config.h:32](../../include/freedom_config.h#L32)

```c
#define FC_SMOOTH_SCROLL_FRAME_MS
```

---

<a id="fc_smooth_scroll_anchor_ms"></a>

### `FC_SMOOTH_SCROLL_ANCHOR_MS`

`macro` | [include/freedom_config.h:35](../../include/freedom_config.h#L35)

```c
#define FC_SMOOTH_SCROLL_ANCHOR_MS
```

A fragment jump under `scroll-behavior: smooth` crosses a whole page, not a wheel notch: longer, like Firefox's smooth scrollIntoView (spec/anchor.md).

---

<a id="fc_anchor_hold_ms"></a>

### `FC_ANCHOR_HOLD_MS`

`macro` | [include/freedom_config.h:38](../../include/freedom_config.h#L38)

```c
#define FC_ANCHOR_HOLD_MS
```

How long a landed document's fragment is re-applied while its height still moves (late images, scripts) and the user has not scrolled (spec/anchor.md 3).

---

<a id="fc_js_fragment_depth"></a>

### `FC_JS_FRAGMENT_DEPTH`

`macro` | [include/freedom_config.h:41](../../include/freedom_config.h#L41)

```c
#define FC_JS_FRAGMENT_DEPTH
```

A hashchange listener that sets the hash again re-enters the fragment navigation; past this depth the request is dropped, like JS_NAV_MAX for redirects (spec/anchor.md 3b).

---

<a id="fc_trusted_js_budget_ms"></a>

### `FC_TRUSTED_JS_BUDGET_MS`

`macro` | [include/freedom_config.h:51](../../include/freedom_config.h#L51)

```c
#define FC_TRUSTED_JS_BUDGET_MS
```

Page-wide script time budget (ms) for a TRUSTED page (allow.conf AND js.conf): a modern app (github's React bundle) needs well over the untrusted 1 s budget in an interpreter.

The user consented to this host; the per-task interrupt still applies. 60 s: the window runs the load off the UI thread, so a heavy app is slow, never frozen.

---

<a id="fc_png_margin"></a>

### `FC_PNG_MARGIN`

`macro` | [include/freedom_config.h:55](../../include/freedom_config.h#L55)

```c
#define FC_PNG_MARGIN
```

Padding around the PNG export canvas (px): the document's content box is FC_PNG_PAGE_W minus twice this.

A page's own <html> margin overrides it.

---

<a id="fc_flex_measure_w"></a>

### `FC_FLEX_MEASURE_W`

`macro` | [include/freedom_config.h:66](../../include/freedom_config.h#L66)

```c
#define FC_FLEX_MEASURE_W
```

Wrap threshold in px used when measuring an item's MAX-CONTENT width: wide enough that no realistic line wraps, small enough to stay far from any overflow in the accumulating pen arithmetic.

A measurement device, not a layout value -- no rendered geometry is ever placed at this width.

---

<a id="fc_flex_min_measure_w"></a>

### `FC_FLEX_MIN_MEASURE_W`

`macro` | [include/freedom_config.h:72](../../include/freedom_config.h#L72)

```c
#define FC_FLEX_MIN_MEASURE_W
```

The other end of the same measuring stick (px): flowed this narrow, every legal break is taken, so the widest resulting line IS the item's MIN-CONTENT width (CSS Sizing 3 5.1).

Like FC_FLEX_MEASURE_W it is a measurement device, not a layout value.

---

<a id="fc_font_chain_max"></a>

### `FC_FONT_CHAIN_MAX`

`macro` | [include/freedom_config.h:77](../../include/freedom_config.h#L77)

```c
#define FC_FONT_CHAIN_MAX
```

Ceiling on the inherited font-size chain the renderer resolves per element.

The chain depth is chosen by the attacker, so this is an anti-DoS bound: the walk is iterative and capped here, never recursive.

---

<a id="fc_max_boxes"></a>

### `FC_MAX_BOXES`

`macro` | [include/freedom_config.h:82](../../include/freedom_config.h#L82)

```c
#define FC_MAX_BOXES
```

Ceiling on the per-page box registry.

Coupled to the out-of-flow resolver's indexed storage by _Static_assert in page_view.c -- a normal page can exceed a lower value, which is a render bug, not a DoS bound.

---

<a id="fc_font_fallback_px"></a>

### `FC_FONT_FALLBACK_PX`

`macro` | [include/freedom_config.h:87](../../include/freedom_config.h#L87)

```c
#define FC_FONT_FALLBACK_PX
```

Fallback font size in px when a text shape carries no resolved size.

Single source for the former scattered 16.0 literals in painters and harnesses; matches the UA root size so fallback text measures like body.

---

<a id="fc_ui_font_size"></a>

### `FC_UI_FONT_SIZE`

`macro` | [include/freedom_config.h:91](../../include/freedom_config.h#L91)

```c
#define FC_UI_FONT_SIZE
```

Chrome font size in px for the minimal Wayland UI shell.

Formerly duplicated as UI_FONT_SIZE in gui/ui_render.c and gui/browser_ui_internal.h.

---

<a id="fc_max_author_css_bytes"></a>

### `FC_MAX_AUTHOR_CSS_BYTES`

`macro` | [include/freedom_config.h:99](../../include/freedom_config.h#L99)

```c
#define FC_MAX_AUTHOR_CSS_BYTES
```

Ceiling on the author CSS text one page may feed the parser: the document's <style> blocks plus its fetched <link> sheets, together.

It is an anti-DoS bound on parser memory and time, and it must sit ABOVE what real pages ship: github.com's front page links ~2.4 MB of distinct CSS, and the former 1 MiB value was consumed by its four colour-theme sheets alone, so the layout sheets that follow them were dropped whole and the page rendered unstyled.

---

<a id="fc_shc_max_text_bytes"></a>

### `FC_SHC_MAX_TEXT_BYTES`

`macro` | [include/freedom_config.h:105](../../include/freedom_config.h#L105)

```c
#define FC_SHC_MAX_TEXT_BYTES
```

Largest stylesheet text (author CSS plus the prepended UA sheet) whose parsed form the worker retains between view derivations (spec/sheet_cache.md).

The retained copy of the text is the cache key, so this bounds that copy; a longer text is parsed on every derivation exactly as before the cache existed.

---

<a id="fc_shc_max_queries"></a>

### `FC_SHC_MAX_QUERIES`

`macro` | [include/freedom_config.h:111](../../include/freedom_config.h#L111)

```c
#define FC_SHC_MAX_QUERIES
```

Most root-matcher questions one parse may record for replay (spec/sheet_cache.md).

Each is a compact selector copy re-asked on every later derivation, so the bound caps both memory and the cost of a hit; a sheet that asks more is simply not retained. Sized against what real pages ask (measured on the allowlist corpus).

---

<a id="fc_mask_cache_bytes"></a>

### `FC_MASK_CACHE_BYTES`

`macro` | [include/freedom_config.h:116](../../include/freedom_config.h#L116)

```c
#define FC_MASK_CACHE_BYTES
```

Blurred box-shadow masks the window retains across frames (spec/mask_cache.md): the byte budget of all retained A8 buffers and how many masks.

A mask is a function of its geometry alone, so it stays valid across scrolls, frames and documents; LRU bounds the memory.

---

<a id="fc_mask_cache_entries"></a>

### `FC_MASK_CACHE_ENTRIES`

`macro` | [include/freedom_config.h:117](../../include/freedom_config.h#L117)

```c
#define FC_MASK_CACHE_ENTRIES
```

---

<a id="fc_lazy_image_margin_px"></a>

### `FC_LAZY_IMAGE_MARGIN_PX`

`macro` | [include/freedom_config.h:120](../../include/freedom_config.h#L120)

```c
#define FC_LAZY_IMAGE_MARGIN_PX
```

Distance (px) beyond the viewport at which a loading="lazy" image starts loading.

---

<a id="fc_tab_op_net_budget_ms"></a>

### `FC_TAB_OP_NET_BUDGET_MS`

`macro` | [include/freedom_config.h:126](../../include/freedom_config.h#L126)

```c
#define FC_TAB_OP_NET_BUDGET_MS
```

Wall time (ms) the trusted parent spends serving ONE worker operation's network requests after the page load (a timer, click or observer callback).

The fetch is synchronous in the GUI thread, so this bounds how long a slow server can freeze the window; once spent, the rest of that operation's requests fail (status 0) instead of blocking.

---

<a id="fc_net_load_settle_ms"></a>

### `FC_NET_LOAD_SETTLE_MS`

`macro` | [include/freedom_config.h:133](../../include/freedom_config.h#L133)

```c
#define FC_NET_LOAD_SETTLE_MS
```

Deferred XHR/fetch delivery (spec/subreq_async.md, "Entrega con plazo").

The first view of a page waits at most FC_NET_LOAD_SETTLE_MS for its in-flight requests (a dead ad host must not hold the page back); what is still running is delivered by later ticks, which the worker asks for at most every FC_NET_POLL_MS while anything is pending (100 ms: an 8 s dead request costs 80 of the window's 240 ticks per load, not all of them).

---

<a id="fc_net_poll_ms"></a>

### `FC_NET_POLL_MS`

`macro` | [include/freedom_config.h:134](../../include/freedom_config.h#L134)

```c
#define FC_NET_POLL_MS
```

---

<a id="fc_net_tick_settle_ms"></a>

### `FC_NET_TICK_SETTLE_MS`

`macro` | [include/freedom_config.h:137](../../include/freedom_config.h#L137)

```c
#define FC_NET_TICK_SETTLE_MS
```

A tick or click waits this long for the requests its handlers issued: a typical API answers in the same operation, as before the plazo existed.

---

<a id="fc_table_track_max_px"></a>

### `FC_TABLE_TRACK_MAX_PX`

`macro` | [include/freedom_config.h:141](../../include/freedom_config.h#L141)

```c
#define FC_TABLE_TRACK_MAX_PX
```

Widest column track (px) a table hands the grid engine: far past any real page, and small enough that TL_MAX_COLS of them sum inside an int.

---
