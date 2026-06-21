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

- **Never phones home.** Any declaration whose value contains `url(` is dropped,
  and all `@`-rules (`@import`, `@font-face`, `@media`, ...) are skipped. So author
  CSS can never trigger a network fetch or a tracking beacon.
- **Bounded (anti-DoS).** Rules, selectors and declarations are capped; over-long
  tokens are ignored. A pathological stylesheet cannot exhaust memory or time.
- **Fail closed.** An unparseable selector or declaration is dropped, never
  guessed. Unknown properties and values are ignored.
- **No execution.** `expression()`, JS URLs, `var()`, `calc()` are not evaluated
  (treated as unknown → ignored).

## Supported subset

**Selectors** (simple / compound, NO combinators): a single compound selector is
an optional type, any number of `.class`, and an optional `#id`, e.g. `p`, `.note`,
`#main`, `a.button`, `*`. Rules may list several comma-separated selectors. A
descendant/child/sibling combinator (space, `>`, `+`, `~`) makes that selector
unsupported (the whole selector is dropped, the rest of the group still parse).
Specificity = `100*has_id + 10*nclasses + has_type`.

**Properties** (whitelist; everything else ignored):

| Property | Resolved into `css_style` |
| :-- | :-- |
| `color` | `color` (packed 0xRRGGBB via css_color), or -1 |
| `background-color`, `background` | `background` (color only; a `background` with `url(` is dropped) |
| `text-align` | `text_align`: left/center/right/justify |
| `font-size` | `font_scale` (percent): `px` relative to 16px base, `em`/`rem` ×100, `%`, and keywords (`small`=85, `medium`=100, `large`=120, `x-large`=150, `xx-large`=200, `smaller`=85, `larger`=120) |
| `font-weight` | `bold`: `bold`/`bolder` or numeric ≥ 600 → 1; `normal`/`lighter`/< 600 → 0 |
| `font-style` | `italic`: `italic`/`oblique` → 1; `normal` → 0 |
| `display` | `display`: `none`/`block`/`inline`/`inline-block`/`flex`/`grid`/other |

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

/* A resolved presentation. Each field uses a sentinel for "unset" so the caller
 * can layer inheritance (take the first ancestor that sets each inheriting one). */
typedef struct css_style {
    int          color;       /* 0xRRGGBB or -1 (unset) */
    int          background;  /* 0xRRGGBB or -1 (unset) */
    css_align    text_align;  /* CSS_ALIGN_UNSET if absent */
    int          font_scale;  /* percent (e.g. 150), or 0 (unset) */
    int          bold;        /* 1, 0, or -1 (unset) */
    int          italic;      /* 1, 0, or -1 (unset) */
    css_display  display;     /* CSS_DISP_UNSET if absent */
} css_style;

typedef struct css_sheet css_sheet;   /* opaque, owns the parsed rules */
```

## API

### `css_status css_parse(const char *text, size_t len, css_sheet **out)`

Parses a `<style>` text (one or many blocks concatenated) into `*out`. Malformed
input never fails: unparseable rules are skipped (`*out` holds what parsed).
`text == NULL` is treated as empty. `out == NULL` => `CSS_ERR_NULL_ARG`; an
allocation failure => `CSS_ERR_OOM`. On `CSS_OK`, `*out` must be freed with
`css_free`. An empty/whitespace text yields a valid empty sheet.

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

- Combinators (descendant/child/sibling), pseudo-classes/elements, attribute
  selectors. `:hover` etc. are dropped.
- Inheritance/`initial`/`inherit`/`unset` keywords (caller does inheritance;
  these keywords are ignored).
- The box model from author CSS (margin/padding/width/border): UA box model still
  governs spacing. `display:flex|grid` *parameters* (gap/justify/columns) keep
  coming from page_view's existing inline parser; `<style>`-driven flex/grid
  parameters are not wired in v1 (only `display:none` from `<style>` takes effect).
- `url()` anything, `@`-rules, `calc()`, `var()`, custom properties, `!important`
  precedence (the token is stripped; it does not raise precedence).
- text-decoration, line-height, letter-spacing, and the rest of CSS.
