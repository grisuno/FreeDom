# spec: css (`css_`)

Pure, I/O-free parser + simple cascade for **author CSS** — the styling the
webmaster wrote, both `<style>` blocks and inline `style=` attributes. Goal: show
the page as intended, with a deliberately **simpler** subset. CSS is hostile
remote content, so this module is the directly auditable surface: it allocates a
bounded model, never fetches anything, and is fuzzed.

It decides nothing about pixels or the network: it parses text into rules and
resolves a *computed presentation* for an element. page_view consults it while
building the display list; render_doc still gates the author presentation behind
`caps.css` (Privacy by Default). Layout structure (flex/grid) is handled elsewhere
and is not gated (doctrine: "Layout != estilo de autor").

## Security posture (non-negotiable)

- **Never phones home.** Any declaration whose value contains `url(` is dropped, and
  the network/font `@`-rules (`@import`, `@font-face`, ...) are skipped. `@media` is
  **parsed** (a safe subset, see below) but can only gate which *local* rules apply;
  it never fetches. So author CSS can never trigger a network fetch or a tracking beacon.
- **Bounded (anti-DoS).** Rules, selectors and declarations are capped; over-long
  tokens are ignored. A pathological stylesheet cannot exhaust memory or time.
- **Fail closed.** An unparseable selector or declaration is dropped, never
  guessed. Unknown properties and values are ignored.
- **No execution.** `expression()`, JS URLs, `var()`, `calc()` are not evaluated
  (treated as unknown → ignored).

## Supported subset

**Selectors** (compound + descendant/child combinators). A **compound** is an
optional type, any number of `.class`, an optional `#id`, and any number of
**attribute selectors** `[...]` (below), e.g. `p`, `.note`, `#main`, `a.button`,
`*`, `input[type=text]`, `a[href^="https"].ext`. A **complex** selector chains
compounds with the **descendant** combinator (whitespace, `A B`) or the **child**
combinator (`A > B`), e.g. `div p`, `nav > a`, `#main .card p`. The rightmost
compound is the *subject* (the element a rule styles); the compounds to its left
constrain its ancestors (descendant = any ancestor; child = the immediate parent).
Up to `CSS_MAX_COMPOUNDS` (4) compounds per selector and `CSS_MAX_ATTR_SEL` (4)
attribute selectors per compound; a deeper chain is **dropped** (fail closed).
Rules may list several comma-separated selectors.

**Attribute selectors** (Hito 23b-4). A compound may carry any number of `[...]`
constraints (up to `CSS_MAX_ATTR_SEL`). The attribute **name** is matched case-
insensitively (HTML); the **value** is case-sensitive unless a trailing `i` flag is
given (`s` forces case-sensitive). Optional single/double quotes around the value
are stripped; a quoted value may contain whitespace (`[title="a b"]`). Supported
operators:

| Syntax | Matches when the attribute… |
| :-- | :-- |
| `[attr]` | is present (any value) |
| `[attr=v]` | equals `v` exactly |
| `[attr~=v]` | is a whitespace-separated list containing the word `v` |
| `[attr\|=v]` | equals `v` or begins with `v-` (e.g. `lang\|=en` ⇒ `en`, `en-US`) |
| `[attr^=v]` | begins with `v` |
| `[attr$=v]` | ends with `v` |
| `[attr*=v]` | contains the substring `v` |

For the word/substring/prefix/suffix operators (`~= ^= $= *=`) an **empty** `v`
never matches (per spec). A malformed `[...]` (missing name, unknown operator,
unbalanced bracket) drops the **whole selector** (fail closed). The host element's
`id`/`class` are also attributes, so `[id=…]`/`[class~=…]` work alongside the
dedicated `#id`/`.class` syntax.

Still **out of scope** (the whole selector is dropped, the rest of the group still
parse): the sibling combinators `+`/`~` and pseudo-classes/elements `:`/`::`.

**Specificity** = sum over all compounds of `100*has_id + 10*(nclasses + nattrs) +
has_type` (an attribute selector counts as a class, so `input[type=text]` = 11 and
`#main .card p` = 100+10+1 = 111). Ties break on document order. Matching is
right-to-left: the subject is tested against the element, then each combinator is
checked against the ancestor chain (descendant backtracks over ancestors).

**`!important` (Hito 23b-4).** A declaration ending in `!important` (optional
whitespace before/inside, case-insensitive) is **honored**, not dropped: the `!important`
suffix is stripped, the value interpreted normally, and the declaration placed in a
**higher cascade tier** that beats every non-important declaration regardless of
specificity. Within the important tier the normal order applies (specificity, then
document order; an **inline** `style=` important beats a `<style>` important because
inline carries the highest specificity). A declaration that is *only* `!important`
(no value) is dropped. This applies to every property, including the box-model
shorthands (`margin: 0 auto !important` stamps all four sides important).

**Properties** (whitelist; everything else ignored):

| Property | Resolved into `css_style` |
| :-- | :-- |
| `color` | `color` (packed 0xRRGGBB via css_color), or -1 |
| `background-color`, `background` | `background` (color only; a `background` with `url(` is dropped) |
| `text-align` | `text_align`: left/center/right/justify |
| `font-size` | `font_scale` (percent): `px` relative to 16px base, `em`/`rem` ×100, `%`, and keywords (`small`=85, `medium`=100, `large`=120, `x-large`=150, `xx-large`=200, `smaller`=85, `larger`=120) |
| `line-height` | `line_scale` (percent of the natural line box): unitless multiplier (`1.5` → 150) or `%` (`160%` → 160), clamped `[CSS_LINE_MIN, CSS_LINE_MAX]`; `normal` → 0 (unset, uses the UA default). Absolute `px`/`em` line-heights are out of scope (dropped). Inherits, like `font-size`. |
| `font-weight` | `bold`: `bold`/`bolder` or numeric ≥ 600 → 1; `normal`/`lighter`/< 600 → 0 |
| `font-style` | `italic`: `italic`/`oblique` → 1; `normal` → 0 |
| `text-decoration`, `text-decoration-line` | `text_decoration` (OR of `CSS_DECO_UNDERLINE`/`CSS_DECO_LINE_THROUGH`/`CSS_DECO_OVERLINE`): collects the line keywords `underline`/`overline`/`line-through` from the (space-separated) value; `none` → 0 (explicit removal — e.g. `a { text-decoration: none }` drops the link underline); a value with *no* line keyword (only a color/style/thickness token) is dropped → unset (-1). Style/color/thickness tokens (`wavy`, `red`, `2px`, `solid`, …) are ignored. |
| `display` | `display`: `none`/`block`/`inline`/`inline-block`/`flex`/`grid`/other |
| `gap`, `grid-gap`, `column-gap` | `gap`: leading px of the value (`12px 8px` → 12; `normal` → 0), clamped `[0, CSS_GAP_MAX]`, or -1 (unset) |
| `justify-content` | `justify`: `flex-start`/`start`→START, `flex-end`/`end`→END, `center`, `space-between`, `space-around`, `space-evenly`; unknown dropped |
| `grid-template-columns` | `grid_cols`: count of whitespace-separated track tokens, clamped `[1, CSS_GRID_COLS_MAX]`, or 0 (unset). `none` is dropped; `repeat()`/`minmax()` are counted as literal tokens (out of scope) |
| `margin`, `margin-top/right/bottom/left` | `margin_top/right/bottom/left` (px). The shorthand expands 1–4 values (CSS order: all / `v h` / `t h b` / `t r b l`). `auto` → `CSS_LEN_AUTO` (meaningful for the horizontal sides: `margin: 0 auto` centers). Negative px allowed. Clamped `[−CSS_LEN_MAX, CSS_LEN_MAX]`. |
| `padding`, `padding-top/right/bottom/left` | `pad_top/right/bottom/left` (px ≥ 0). Same 1–4 shorthand. `auto`/negative → that side dropped (fail closed). Clamped `[0, CSS_LEN_MAX]`. |
| `width` | `width` (px content width, or `CSS_LEN_UNSET`). `auto` → unset. |
| `max-width` | `max_width` (px, or `CSS_LEN_UNSET`). `none` → unset. |
| `font-family` | `font_family` (`css_font_family`): the first recognised name in the comma stack maps to its **generic bucket** (`serif`/`sans-serif`/`monospace`/`cursive`/`fantasy`); common names (Arial→sans, Times→serif, Courier→mono, …) are mapped; quotes stripped; `url()` dropped; unknown → unset |
| `text-transform` | `text_transform` (`css_text_transform`): `uppercase`/`lowercase`/`capitalize`/`none` (explicit); other values (`full-width`, …) dropped |
| `letter-spacing` | `letter_spacing` (signed px; `normal` → 0; `em` ×16; `CSS_LEN_UNSET` unset), clamped `[−CSS_SPACING_MAX, CSS_SPACING_MAX]`; `%`/`calc`/bare number dropped |
| `word-spacing` | `word_spacing` (same domain/clamp as `letter-spacing`) — extra px added to each inter-word gap |
| `text-shadow` | `shadow_dx`/`shadow_dy` (signed px offsets, clamped `[−CSS_SHADOW_MAX, CSS_SHADOW_MAX]`) + `shadow_color` (0xRRGGBB, or -1 = none/unset). Single layer: collects ≤3 lengths (dx, dy, **blur ignored**) + one color in any order; needs both offsets or the declaration is dropped; missing color → black; `none` → explicit no-shadow; `url()` dropped |
| `opacity` | `opacity` (percent 0..100, or -1 unset): unitless `0..1` ×100 or a `%`, clamped `[0,100]` |
| `vertical-align` | `valign` (`css_valign`): `baseline`/`sub`/`super` only; `top`/`middle`/`bottom`/`<length>` dropped (out of scope) |
| `text-indent` | `text_indent` (signed px first-line indent; `em` ×16; `CSS_LEN_UNSET` unset); `%`/viewport dropped |
| `white-space` | `white_space` (`css_white_space`): `normal`/`nowrap`/`pre`/`pre-wrap`/`pre-line` — the presentation layer consumes only the **wrap/no-wrap** distinction (`nowrap`/`pre` suppress line wrapping) |
| `list-style-type`, `list-style` | `list_style` (`css_list_style`): the first recognised type keyword wins (`disc`/`circle`/`square`/`decimal`/`lower-alpha`\|`lower-latin`/`upper-alpha`\|`upper-latin`/`lower-roman`/`upper-roman`/`none`); changes the `<li>` marker; `url()` (list-style-image) dropped (never fetch) |

### Property inventory (supported vs missing)

**Supported** (resolved into `css_style`, gated downstream as noted):

- *Color / background*: `color`, `background-color`, `background` (color only).
- *Text*: `text-align`, `font-size`, `font-weight`, `font-style`, `line-height`,
  `text-decoration`(`-line`), **`font-family`**, **`text-transform`**,
  **`letter-spacing`**, **`word-spacing`**, **`text-shadow`**, **`opacity`**,
  **`vertical-align`**, **`text-indent`**, **`white-space`** (wrap/no-wrap only).
- *Layout / box*: `display`, `gap`(`grid-gap`/`column-gap`), `justify-content`,
  `grid-template-columns`, `margin`(+longhands), `padding`(+longhands), `width`,
  `max-width`.
- *Lists*: **`list-style-type`**, **`list-style`** (type token only).
- *At-rules / cascade*: `@media` (subset: `prefers-color-scheme`, `screen`/`print`/
  `all`, `min/max-width`), `!important`.

(Properties in **bold** are the Hito 23b-6 batch.)

**Not yet supported** (dropped / fail closed unless noted), highest cosmetic value
first:

- *Box decoration*: `border`(/`-width`/`-style`/`-color`), `border-radius`,
  `box-shadow`, `box-sizing`, `outline` — need per-block box grouping (the flat
  display list has no block box to stroke yet).
- *Positioning*: `position` (relative/absolute/sticky/fixed), `top`/`left`/…,
  `z-index`, `float`, `clear`, `overflow`.
- *Backgrounds beyond a solid color*: `background-image`/gradients (and any
  `url()` — by doctrine, never fetched), `background-position`/`-size`/`-repeat`.
- *Transforms / filters / transitions*: `transform`, `filter`, `transition`,
  `animation`, `@keyframes`.
- *Text, finer grain*: `text-transform: full-width`, `letter-spacing`/`text-indent`
  in `%`/viewport units, `text-decoration-style`/`-color`/`-thickness`,
  `vertical-align` length/`top`/`middle`/`bottom`, `white-space` whitespace
  *preservation* (only the wrap distinction is consumed), `word-break`,
  `overflow-wrap`, `text-overflow`, `direction`/`writing-mode`.
- *Flex/grid, finer grain*: per-item `flex-grow`/`-shrink`/`-basis`/`order`,
  `align-items`/`align-content`, distinct `row-gap`, `repeat()`/`minmax()`/`fr`
  weights/named tracks.
- *Selectors*: sibling combinators `+`/`~`, pseudo-classes/elements `:`/`::`.
- *Values*: `calc()`, `var()`/custom properties, `url()` anything,
  `@import`/`@font-face`.

**Text-presentation extensions (Hito 23b-6).** `font-family` / `text-transform` /
`letter-spacing` / `word-spacing` / `text-shadow` / `opacity` / `vertical-align` /
`text-indent` / `white-space` resolve through the **same cascade** as the other
properties (a `<style>` rule, a selector, and inline `style=` all feed them, inline
winning, `!important` honored). In CSS they all **inherit**; in this flat model the
caller (page_view) takes the value from the **nearest ancestor** that sets each, exactly
like `color`. They are **presentation**, so render_doc applies them only with `caps.css`
(Privacy/Secure by Default), like the author colors. `font-family` maps a name to a
**generic bucket** (the engine has no font files to match exact families); `text-shadow`
keeps a single layer (blur ignored); `white-space` consumes only the wrap/no-wrap
distinction; `list-style-type` changes the `<li>` marker (structural — page_view bakes it
into the run text, so it is carried by default, not gated). None can ever phone home:
`url()` (a `@font-face`/list-style-image) is dropped on every one of them.

**Box model (Hito 23b-3).** `margin` / `padding` / `width` / `max-width` resolve through the
**same cascade** as the other properties (a `<style>` rule, a selector, and inline `style=`
all feed them, inline winning). **Lengths** accept `px`, a bare `0`, and `em`/`rem` (×16 px,
the engine's base font); `%`/`vw`/`vh`/`calc()` and other units are **dropped** (fail closed —
they need a containing-block width the parser does not have). They are **not inherited** (a box
describes its own element, so page_view reads them from that element's resolved style, not up
the ancestor chain). page_view turns them into a per-block placement (left/right inset, an
optional width cap, a centered flag, and a top/bottom margin override) that the presentation
layer applies; like the author *colors* and `text-align`/`font-size`, the **box is gated behind
`caps.css`** (Privacy/Secure by Default — author box metrics can shrink content to
unreadability, so they stay off until the user opts in). The geometry math (cap + centering +
insets within an available width) lives in the pure, tested `box_style` helper `bx_place`.

**Out of scope of the box model (v1, Hito 23b-3), fail closed / UA fallback:** vertical
`padding-top/bottom` application (parsed and stored, but the flat display list has no per-block
box to inflate yet — needs the box-grouping of a later milestone), `border` (width/style/color),
`box-sizing` (every `width` is treated as a content-box width), `%`/viewport units, and
**nested** author boxes do not compose (the nearest block ancestor that sets a box wins for the
horizontal placement; an outer wrapper's `max-width`/centering still reaches its descendants
because they all share that ancestor).

**Container layout params (Hito 23b-2).** `gap` / `justify-content` / `grid-template-columns`
resolve through the **same cascade** as the other properties (so a `<style>` rule, a
compound/id selector, and an inline `style=` all feed them, inline winning). They are
**not inherited** (they describe the flex/grid container element itself, so the caller
reads them from that element's resolved style, not up the ancestor chain). page_view
consumes them to parameterize the flex/grid layout, which is **always applied and not
gated by `caps.css`** (doctrine: "Layout != estilo de autor" — geometry is structure, it
opens no socket and leaks nothing). Only author *colors* stay behind `caps.css`.

**`@media` (Hito 23b).** A `@media <query> { ... }` block is **parsed**, not dropped: its
inner rules are kept **only if the query matches** the render-time `css_media` context
(`css_parse_media`), evaluated at parse time. Supported query features:

- media **types** `screen` / `print` / `all` (and a leading `only`, which is ignored);
- `(prefers-color-scheme: dark|light)` — matches `media.prefers_dark` (auto dark mode);
- `(min-width: Npx)` / `(max-width: Npx)` — compared against `media.width_px` (a fixed,
  normalized desktop width, so it leaks no real viewport size — anti-fingerprinting).

A query list is comma-separated (**OR**); within a query, parts are joined by `and`
(**AND**). **Fail closed:** `not`, unknown media types, and unknown features make that
query (segment) **not match** — Freedom never applies a rule it cannot correctly gate.
Nested `@media` and any other `@`-rule inside a matched block are skipped. `@import` /
`@font-face` / other top-level `@`-rules are still skipped entirely (no network/font surface).

## Types

```c
typedef enum css_status { CSS_OK = 0, CSS_ERR_NULL_ARG, CSS_ERR_OOM } css_status;

typedef enum css_align {        /* text-align */
    CSS_ALIGN_UNSET = 0, CSS_ALIGN_LEFT, CSS_ALIGN_CENTER,
    CSS_ALIGN_RIGHT, CSS_ALIGN_JUSTIFY
} css_align;

typedef enum css_display {
    CSS_DISP_UNSET = 0, CSS_DISP_NONE, CSS_DISP_BLOCK, CSS_DISP_INLINE,
    CSS_DISP_INLINE_BLOCK, CSS_DISP_FLEX, CSS_DISP_GRID, CSS_DISP_OTHER
} css_display;

typedef enum css_justify {      /* justify-content (flex/grid main axis) */
    CSS_JUSTIFY_UNSET = 0, CSS_JUSTIFY_START, CSS_JUSTIFY_END, CSS_JUSTIFY_CENTER,
    CSS_JUSTIFY_SPACE_BETWEEN, CSS_JUSTIFY_SPACE_AROUND, CSS_JUSTIFY_SPACE_EVENLY
} css_justify;

/* A resolved presentation. Each field uses a sentinel for "unset" so the caller
 * can layer inheritance (take the first ancestor that sets each inheriting one).
 * The flex/grid container fields (gap/justify/grid_cols) are NOT inherited. */
typedef struct css_style {
    int          color;       /* 0xRRGGBB or -1 (unset) */
    int          background;  /* 0xRRGGBB or -1 (unset) */
    css_align    text_align;  /* CSS_ALIGN_UNSET if absent */
    int          font_scale;  /* percent (e.g. 150), or 0 (unset) */
    int          line_scale;  /* line-height percent of the natural line box, or 0 (unset) */
    int          text_decoration; /* OR of CSS_DECO_*; 0 = none; -1 = unset */
    int          bold;        /* 1, 0, or -1 (unset) */
    int          italic;      /* 1, 0, or -1 (unset) */
    css_display  display;     /* CSS_DISP_UNSET if absent */
    int          gap;         /* px between flex/grid items, or -1 (unset) */
    css_justify  justify;     /* justify-content; CSS_JUSTIFY_UNSET if absent */
    int          grid_cols;   /* grid-template-columns track count, or 0 (unset) */
    /* Author box model (not inherited; px). margins: CSS_LEN_UNSET / CSS_LEN_AUTO
     * (auto) / signed px. padding: CSS_LEN_UNSET / px >= 0. width/max_width:
     * CSS_LEN_UNSET / px > 0. */
    int          margin_top, margin_right, margin_bottom, margin_left;
    int          pad_top, pad_right, pad_bottom, pad_left;
    int          width, max_width;
    /* Text-presentation extensions (Hito 23b-6; inherit in CSS, gated by caps.css). */
    int          font_family;     /* css_font_family, 0 unset */
    int          text_transform;  /* css_text_transform, 0 unset */
    int          letter_spacing;  /* signed px, 0 = normal, CSS_LEN_UNSET unset */
    int          word_spacing;    /* signed px, 0 = normal, CSS_LEN_UNSET unset */
    int          shadow_dx, shadow_dy; /* text-shadow offsets px (0 if no shadow) */
    int          shadow_color;    /* 0xRRGGBB, or -1 (none/unset) */
    int          opacity;         /* percent 0..100, or -1 unset */
    int          valign;          /* css_valign, 0 unset */
    int          text_indent;     /* signed px, CSS_LEN_UNSET unset */
    int          white_space;     /* css_white_space, 0 unset */
    int          list_style;      /* css_list_style, 0 unset */
} css_style;

typedef enum css_font_family {    /* font-family generic bucket */
    CSS_FF_UNSET = 0, CSS_FF_SERIF, CSS_FF_SANS, CSS_FF_MONO,
    CSS_FF_CURSIVE, CSS_FF_FANTASY
} css_font_family;
typedef enum css_text_transform {
    CSS_TT_UNSET = 0, CSS_TT_NONE, CSS_TT_UPPERCASE, CSS_TT_LOWERCASE, CSS_TT_CAPITALIZE
} css_text_transform;
typedef enum css_valign { CSS_VA_UNSET = 0, CSS_VA_BASELINE, CSS_VA_SUB, CSS_VA_SUPER } css_valign;
typedef enum css_white_space {
    CSS_WS_UNSET = 0, CSS_WS_NORMAL, CSS_WS_NOWRAP, CSS_WS_PRE, CSS_WS_PRE_WRAP, CSS_WS_PRE_LINE
} css_white_space;
typedef enum css_list_style {
    CSS_LS_UNSET = 0, CSS_LS_NONE, CSS_LS_DISC, CSS_LS_CIRCLE, CSS_LS_SQUARE,
    CSS_LS_DECIMAL, CSS_LS_LOWER_ALPHA, CSS_LS_UPPER_ALPHA, CSS_LS_LOWER_ROMAN, CSS_LS_UPPER_ROMAN
} css_list_style;

#define CSS_SPACING_MAX 200      /* px clamp for letter/word-spacing (anti-DoS) */
#define CSS_SHADOW_MAX  100      /* px clamp for text-shadow offsets (anti-DoS) */
#define CSS_GAP_MAX       4096   /* px cap on gap (anti-DoS) */
#define CSS_GRID_COLS_MAX 64     /* cap on grid-template-columns tracks (anti-DoS) */
#define CSS_MAX_COMPOUNDS 4      /* max compounds in one complex selector */
#define CSS_MAX_ATTR_SEL  4      /* max [attr] selectors in one compound */
#define CSS_LINE_MIN      50     /* line-height clamp floor (percent) */
#define CSS_LINE_MAX      400    /* line-height clamp ceiling (percent, anti-DoS) */
#define CSS_DECO_UNDERLINE    0x1 /* text-decoration line bits (OR-combined) */
#define CSS_DECO_LINE_THROUGH 0x2
#define CSS_DECO_OVERLINE     0x4
#define CSS_LEN_MAX       100000 /* px clamp for box-model lengths (anti-DoS) */
#define CSS_LEN_UNSET     (-2147483647 - 1) /* INT_MIN: box length not set */
#define CSS_LEN_AUTO      (-2147483647)     /* INT_MIN+1: the 'auto' keyword */

typedef struct css_sheet css_sheet;   /* opaque, owns the parsed rules */

/* Render-time media context for evaluating @media at parse time. width_px is a
 * fixed, normalized desktop width (no real viewport size leaks). */
typedef struct css_media {
    int prefers_dark; /* 1: user prefers a dark color scheme */
    int print;        /* 1: rendering for print (PDF); 0: screen */
    int width_px;     /* assumed viewport width for min/max-width (default 1920) */
} css_media;

#define CSS_MEDIA_DEFAULT_WIDTH 1920
```

## API

### `css_status css_parse(const char *text, size_t len, css_sheet **out)`

Parses a `<style>` text (one or many blocks concatenated) into `*out`. Malformed
input never fails: unparseable rules are skipped (`*out` holds what parsed).
`text == NULL` is treated as empty. `out == NULL` => `CSS_ERR_NULL_ARG`; an
allocation failure => `CSS_ERR_OOM`. On `CSS_OK`, `*out` must be freed with
`css_free`. An empty/whitespace text yields a valid empty sheet. Equivalent to
`css_parse_media` with a default **screen / light / 1920px** context (so plain
`@media screen`/`(min-width:…)` blocks apply, `prefers-color-scheme: dark` does not).

### `css_status css_parse_media(const char *text, size_t len, const css_media *media, css_sheet **out)`

As `css_parse`, but `@media` blocks are gated against `media` (see *Supported subset*).
`media == NULL` uses the default screen/light/1920px context. The matched rules are
folded into the sheet as if unconditional, so `css_resolve` is unchanged.

### `void css_free(css_sheet *s)`

Idempotent; NULL-safe.

### `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id, const char *const *classes, size_t nclasses, const char *inline_style, size_t inline_len)`

Computes the presentation for one element. Considers every `sheet` rule whose
selector matches `(tag, id, classes)`, applied in cascade order (lower specificity
first, ties broken by document order), then the element's own `inline_style`
declarations (which win over any rule). Returns a `css_style` with the winning
value for each property (or its unset sentinel). `sheet`/`tag` may be NULL (an
empty sheet / no tag); `inline_style` may be NULL. Pure, allocates nothing,
re-entrant. Inheritance is the **caller's** job (call per ancestor, merge unset
fields).

This signature carries no ancestor context, so it matches **only single-compound**
selectors (a complex selector with a combinator never matches through it). It is
equivalent to `css_resolve_el` with a parentless element; kept for callers that do
not need combinators.

### `css_style css_resolve_el(const css_sheet *sheet, const css_element *el, const char *inline_style, size_t inline_len)`

As `css_resolve`, but `el` describes the element **and its ancestor chain** (`el`,
`el->parent`, `el->parent->parent`, …, NULL at the root), so **combinator** rules
(`div p`, `nav > a`) can be matched: the subject compound is tested against `el` and
each combinator is checked up the chain. `el == NULL` resolves only the inline
declarations. `css_element` is:

```c
typedef struct css_attr {             /* one element attribute for [attr] selectors */
    const char *name;                 /* lowercased local name */
    const char *value;                /* attribute value ("" if empty) */
} css_attr;

typedef struct css_element {
    const char *tag;                  /* lowercased local name, or NULL */
    const char *id;                   /* id attribute value, or NULL */
    const char *const *classes;       /* class tokens (not NUL-joined) */
    size_t nclasses;
    const css_attr *attrs;            /* element attributes, or NULL (for [attr] selectors) */
    size_t nattrs;
    const struct css_element *parent; /* parent element, or NULL at the root */
} css_element;
```

The caller supplies as much of the chain as it has (bounded is fine: a missing deep
ancestor only means a descendant selector against it fails to match — fail closed).
`attrs`/`nattrs` may be empty (`NULL`/`0`): an attribute selector against an element
with no attribute list simply does not match. Pure, allocates nothing, re-entrant.

### `css_style css_parse_inline(const char *style, size_t len)`

Convenience: `css_resolve(NULL, NULL, NULL, NULL, 0, style, len)` — resolve only
an inline declaration list. (May be expressed as the same call; kept for the
common case.)

## Guarantees

- **Containment of effects.** The output is a small value struct; nothing the
  parser reads can cause a fetch, a write, or unbounded work.
- **Determinism.** Same input → same `css_style`. Cascade order is specificity
  then document order then inline-wins; stable.
- **Pure & reentrant.** No global state, no I/O; the only allocation is the sheet
  (freed by `css_free`).

## Out of scope (v1)

- The **sibling** combinators `+`/`~` and pseudo-classes/elements (`:hover`/`::before`)
  — dropped (fail closed). Descendant (` `) and child (`>`) combinators **are**
  supported (up to `CSS_MAX_COMPOUNDS` compounds); **attribute** selectors `[attr]`,
  `[attr=v]`, `~=`, `|=`, `^=`, `$=`, `*=` (with the `i`/`s` case flag) are supported
  (Hito 23b-4, up to `CSS_MAX_ATTR_SEL` per compound).
- Inheritance/`initial`/`inherit`/`unset` keywords (caller does inheritance;
  these keywords are ignored).
- The author box model `margin`/`padding`/`width`/`max-width` **is now resolved through the
  cascade** (Hito 23b-3) and applied (gated by `caps.css`): horizontal insets, an optional
  width cap, `margin: 0 auto` centering, and a top/bottom margin override. Still out of scope:
  `border`, `box-sizing`, vertical `padding-top/bottom` application, `%`/viewport units, and
  nested box composition (see *Box model* above). `display:flex|grid` *parameters*
  (`gap`/`justify-content`/`grid-template-columns`) are resolved through the cascade (Hito
  23b-2). Still out of scope: per-item flex (`flex-grow`/`flex-shrink`/`flex-basis`/`order`),
  `align-items`/`align-content`, `row-gap` as distinct from `column-gap`, `repeat()`/`minmax()`
  track expansion, and named/`auto`/`fr`-weighted grid tracks (every track is treated as 1fr
  equal-width).
- `url()` anything, `@import`/`@font-face`/other `@`-rules, `calc()`, `var()`, custom
  properties. `!important` **is** honored (Hito 23b-4): the suffix is stripped and the
  declaration raised to a higher cascade tier (was previously dropped). `@media` is
  supported (subset above); `not`/unknown features fail closed.
- `position` (relative/absolute/sticky) and other layout/box properties — deferred to
  the layout milestone (Hito 23b-2); `@media print` *rendering* into the PDF is deferred
  (print-only rules are correctly excluded from the screen view today).
- `text-decoration` (and `text-decoration-line`) **is** supported for the line keywords
  `underline`/`overline`/`line-through`/`none` (Hito 23b-5; gated by `caps.css`). Still out of
  scope: `text-decoration-style`/`-color`/`-thickness` (extra tokens are ignored, not applied),
  `text-decoration` propagation semantics (our flat model resolves the nearest ancestor that set
  it, like `color`).
- **`font-family`, `text-transform`, `letter-spacing`, `word-spacing`, `text-shadow`,
  `opacity`, `vertical-align`, `text-indent`, `white-space`, `list-style-type`/`list-style`**
  **are** supported (Hito 23b-6; see *Property inventory* and the *Properties* table for the
  exact subset and fail-closed rules). Still out of scope within them: exact font matching
  (only generic buckets), `text-shadow` blur/multi-layer, `%`/viewport `letter-spacing`/
  `text-indent`, `vertical-align` lengths/`top`/`middle`/`bottom`, and `white-space`
  whitespace *preservation* (only the wrap distinction is consumed). The full "Not yet
  supported" list (borders, `position`, transforms, gradients, …) is in *Property inventory*.
