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
optional type, any number of `.class`, and an optional `#id`, e.g. `p`, `.note`,
`#main`, `a.button`, `*`. A **complex** selector chains compounds with the
**descendant** combinator (whitespace, `A B`) or the **child** combinator (`A > B`),
e.g. `div p`, `nav > a`, `#main .card p`. The rightmost compound is the *subject*
(the element a rule styles); the compounds to its left constrain its ancestors
(descendant = any ancestor; child = the immediate parent). Up to
`CSS_MAX_COMPOUNDS` (4) compounds per selector; a deeper chain is **dropped**
(fail closed). Rules may list several comma-separated selectors.

Still **out of scope** (the whole selector is dropped, the rest of the group still
parse): the sibling combinators `+`/`~`, attribute selectors `[...]`, and
pseudo-classes/elements `:`/`::`.

**Specificity** = sum over all compounds of `100*has_id + 10*nclasses + has_type`
(so `#main .card p` = 100+10+1 = 111). Ties break on document order. Matching is
right-to-left: the subject is tested against the element, then each combinator is
checked against the ancestor chain (descendant backtracks over ancestors).

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
| `display` | `display`: `none`/`block`/`inline`/`inline-block`/`flex`/`grid`/other |
| `gap`, `grid-gap`, `column-gap` | `gap`: leading px of the value (`12px 8px` → 12; `normal` → 0), clamped `[0, CSS_GAP_MAX]`, or -1 (unset) |
| `justify-content` | `justify`: `flex-start`/`start`→START, `flex-end`/`end`→END, `center`, `space-between`, `space-around`, `space-evenly`; unknown dropped |
| `grid-template-columns` | `grid_cols`: count of whitespace-separated track tokens, clamped `[1, CSS_GRID_COLS_MAX]`, or 0 (unset). `none` is dropped; `repeat()`/`minmax()` are counted as literal tokens (out of scope) |

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
    int          bold;        /* 1, 0, or -1 (unset) */
    int          italic;      /* 1, 0, or -1 (unset) */
    css_display  display;     /* CSS_DISP_UNSET if absent */
    int          gap;         /* px between flex/grid items, or -1 (unset) */
    css_justify  justify;     /* justify-content; CSS_JUSTIFY_UNSET if absent */
    int          grid_cols;   /* grid-template-columns track count, or 0 (unset) */
} css_style;

#define CSS_GAP_MAX       4096   /* px cap on gap (anti-DoS) */
#define CSS_GRID_COLS_MAX 64     /* cap on grid-template-columns tracks (anti-DoS) */
#define CSS_LINE_MIN      50     /* line-height clamp floor (percent) */
#define CSS_LINE_MAX      400    /* line-height clamp ceiling (percent, anti-DoS) */

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
typedef struct css_element {
    const char *tag;                  /* lowercased local name, or NULL */
    const char *id;                   /* id attribute value, or NULL */
    const char *const *classes;       /* class tokens (not NUL-joined) */
    size_t nclasses;
    const struct css_element *parent; /* parent element, or NULL at the root */
} css_element;
```

The caller supplies as much of the chain as it has (bounded is fine: a missing deep
ancestor only means a descendant selector against it fails to match — fail closed).
Pure, allocates nothing, re-entrant.

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

- The **sibling** combinators `+`/`~`, pseudo-classes/elements (`:hover`/`::before`),
  and attribute selectors `[...]` — dropped (fail closed). Descendant (` `) and
  child (`>`) combinators **are** supported (up to `CSS_MAX_COMPOUNDS` compounds).
- Inheritance/`initial`/`inherit`/`unset` keywords (caller does inheritance;
  these keywords are ignored).
- The box model from author CSS (margin/padding/width/border): UA box model still
  governs spacing. `display:flex|grid` *parameters* (`gap`/`justify-content`/
  `grid-template-columns`) **are now resolved through the cascade** (Hito 23b-2), so a
  `<style>` rule feeds them, not only inline `style=`. Still out of scope: per-item
  flex (`flex-grow`/`flex-shrink`/`flex-basis`/`order`), `align-items`/`align-content`,
  `row-gap` as distinct from `column-gap`, `repeat()`/`minmax()` track expansion, and
  named/`auto`/`fr`-weighted grid tracks (every track is treated as 1fr equal-width).
- `url()` anything, `@import`/`@font-face`/other `@`-rules, `calc()`, `var()`, custom
  properties, `!important` precedence (the token is stripped; it does not raise it).
  `@media` is supported (subset above); `not`/unknown features fail closed.
- `position` (relative/absolute/sticky) and other layout/box properties — deferred to
  the layout milestone (Hito 23b-2); `@media print` *rendering* into the PDF is deferred
  (print-only rules are correctly excluded from the screen view today).
- text-decoration, line-height, letter-spacing, and the rest of CSS.
