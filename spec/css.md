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
  `CSS_MAX_RULES`/`CSS_MAX_SELS`/`CSS_MAX_DECLS` (css.c) were raised 16x
  (384/512/2048 → 6144/8192/32768) on 2026-07-09 after a real vendored, minified
  Bootstrap 4.5.2 stylesheet (~2100 rules) showed the old `CSS_MAX_RULES` silently
  dropping essentially every utility class past rule #384 — the symptom was "the
  whole page ignores `.bg-dark`/`.text-success`/etc." with no error anywhere,
  since truncation here is deliberate and silent. Still a hard, finite cap (a
  hostile sheet is still bounded), just sized for one real component-library
  stylesheet instead of a toy one. Paired with `pv_style_cache` in page_view.c
  (memoizes `cch_element_style()` per element pointer, since a shared ancestor is
  otherwise re-resolved once per descendant) so the larger cap does not multiply
  page_view's runtime by every text node on the page.
- **Fail closed.** An unparseable selector or declaration is dropped, never
  guessed. Unknown properties and values are ignored.
- **No execution.** `expression()` and JS URLs are not evaluated (treated as
  unknown → ignored). `var()` and `calc()` **are** evaluated (see below), but purely
  as bounded, allocation-light **text substitution and arithmetic** over values this
  module already understands — never code, never a fetch, never unbounded (custom
  properties are a fixed-size table, `calc()`/`var()` recursion is depth-capped).

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

**Sibling combinators (Hito 23b-9).** A complex selector may also join compounds
with the **adjacent-sibling** (`A + B`) and **general-sibling** (`A ~ B`)
combinators: `+` requires B's immediately preceding element sibling to match A;
`~` requires *some* preceding element sibling to match. Matching walks the
`css_element.prev` chain the caller supplies; **an element without `prev` links
simply never matches through a sibling combinator (fail closed)**. page_view
builds the prev chain for the **subject element only**, bounded to
`PV_CSS_SIB_MAX` (16) preceding siblings — a sibling combinator on a non-subject
compound (e.g. the `+` in `h1 + div p`) or a sibling further left than the bound
does not match. Common real-world forms (`li + li`, `h2 + p`,
`input:checked + label`, `h2 ~ p`) are all subject-level.

**Pseudo-classes (Hito 23b-9).** A compound may carry up to `CSS_MAX_PSEUDO_SEL`
(4) pseudo-classes. Each counts **10** toward specificity (like a class).
Supported, with their Zero-Knowledge/static-render semantics:

| Pseudo-class | Matches when… |
| :-- | :-- |
| `:link`, `:any-link` | the element is `a`/`area` **with an `href` attribute`**. Zero Knowledge: Freedom keeps no history, so every link is unvisited and `:link` covers them all. |
| `:visited` | **never** (no history by design — CSS history sniffing is impossible). |
| `:hover`, `:active`, `:focus`, `:focus-within`, `:focus-visible` | **never** (the cascade is resolved once per load; there is no interactive state plumbing yet). Parsed so the selector and its group survive. |
| `:root` | the element's tag is `html`. |
| `:first-child` | `el->nth == 1`. |
| `:last-child` | `el->nth == el->nsib` (both known). |
| `:only-child` | `nth == 1 && nsib == 1`. |
| `:nth-child(An+B)` | the 1-based sibling index `nth` satisfies `nth = A*m + B` for some integer `m >= 0`. Accepts `odd`, `even`, `N`, `An`, `An+B`, `An-B`, `-n+B`, `n` (case-insensitive, spaces around the sign allowed). `\|A\|`/`\|B\|` bounded by `CSS_NTH_MAX` (100000); malformed or out-of-bounds drops the selector. |
| `:nth-last-child(An+B)` | same formula over the index counted **from the end** (`nsib - nth + 1`). |
| `:checked` | the element has a `checked` attribute (static form state). |
| `:disabled` | the element has a `disabled` attribute. |
| `:enabled` | the element is a form control (`input`/`button`/`select`/`textarea`/`option`/`optgroup`/`fieldset`) **without** a `disabled` attribute. |

The structural pseudo-classes read `css_element.nth`/`.nsib` (1-based index among
element siblings / total element siblings). **`0` means unknown, and unknown never
matches** (fail closed): callers that cannot afford the sibling walk simply lose
structural matching, never mis-match. page_view computes both with a bounded walk
(`PV_CSS_NTH_MAX`, 1024): an element beyond 1024 element-siblings reads as unknown.

**Unknown pseudo-classes and all pseudo-elements** (`::before`, `::after`,
`::selection`, …, including the legacy single-colon spellings `:before`/`:after`/
`:first-line`/`:first-letter`, and functional ones we do not support such as
`:not()`/`:is()`/`:where()`/`:has()`/`:first-of-type`) drop the **whole selector**
(fail closed); the rest of the comma group still parses.

**Specificity** = sum over all compounds of `100*has_id + 10*(nclasses + nattrs +
npseudo) + has_type` (an attribute selector and a pseudo-class each count as a
class, so `input[type=text]` = 11, `a:link` = 11 and `#main .card p` = 100+10+1 =
111). Ties break on document order. Matching is right-to-left: the subject is
tested against the element, then each combinator is checked against the ancestor
(`parent`) or preceding-sibling (`prev`) chain (descendant/`~` backtrack).

The selector engine (types, parser, matcher) lives in the split-out module
**`css_select`** (`include/css_select.h` + `src/css_select.c`, entry points
`csel_parse`/`csel_matches`); see `spec/css_select.md`. The cascade and value
interpretation stay here in `css`.

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
| `text-decoration`, `text-decoration-line` | `text_decoration` (OR of `CSS_DECO_UNDERLINE`/`CSS_DECO_LINE_THROUGH`/`CSS_DECO_OVERLINE`): collects the line keywords `underline`/`overline`/`line-through` from the (space-separated) value; `none` → 0 (explicit removal — e.g. `a { text-decoration: none }` drops the link underline); a value with *no* line keyword (only a color/style/thickness token) is dropped → unset (-1). Style/color/thickness tokens (`wavy`, `red`, `2px`, `solid`, …) are **no longer** ignored if they reach the dedicated properties below: the combined shorthand still extracts only line keywords. |
| `text-decoration-color` | `text_decoration_color` (0xRRGGBB or -1 unset): colour of the decoration line. Parsed by `interp_color`. |
| `text-decoration-style` | `text_decoration_style` (`css_text_decoration_style`): `solid`/`double`/`dotted`/`dashed`/`wavy`; unknown → unset. |
| `display` | `display`: `none`/`block`/`inline`/`inline-block`/`flex`/`grid`/other |
| `gap`, `grid-gap`, `column-gap` | `gap`: leading px of the value (`12px 8px` → 12; `normal` → 0), clamped `[0, CSS_GAP_MAX]`, or -1 (unset) |
| `justify-content` | `justify`: `flex-start`/`start`→START, `flex-end`/`end`→END, `center`, `space-between`, `space-around`, `space-evenly`; unknown dropped |
| `grid-template-columns` | `grid_cols`: track **count**, clamped `[1, CSS_GRID_COLS_MAX]`, or 0 (unset). `none` is dropped. `repeat(N, track-list)` expands to `N * tracks-in-pattern` (`repeat(auto-fill\|auto-fit, ...)` needs an available width this pure parser does not have, so it fails the WHOLE value); `minmax(a,b)` counts as ONE track. Track **sizes** (incl. `fr` weights) are still not resolved — every counted track lays out as an equal-width column downstream (see *Container layout params* below) |
| `margin`, `margin-top/right/bottom/left` | `margin_top/right/bottom/left` (px). The shorthand expands 1–4 values (CSS order: all / `v h` / `t h b` / `t r b l`). `auto` → `CSS_LEN_AUTO` (meaningful for the horizontal sides: `margin: 0 auto` centers). Negative px allowed. Clamped `[−CSS_LEN_MAX, CSS_LEN_MAX]`. |
| `padding`, `padding-top/right/bottom/left` | `pad_top/right/bottom/left` (px ≥ 0). Same 1–4 shorthand. `auto`/negative → that side dropped (fail closed). Clamped `[0, CSS_LEN_MAX]`. |
| `width` | `width` (px content width, or `CSS_LEN_UNSET`). `auto` → unset. |
| `min-width` | `min_width` (px, or `CSS_LEN_UNSET`). `auto` → unset. Same units as `width`; negative dropped. |
| `max-width` | `max_width` (px, or `CSS_LEN_UNSET`). `none` → unset. |
| `height` | `height` (px, or `CSS_LEN_UNSET`). `auto` → unset. Same units as `width`; negative dropped. |
| `min-height` | `min_height` (px, or `CSS_LEN_UNSET`). `auto`/`none` → unset. Same units; negative dropped. |
| `max-height` | `max_height` (px, or `CSS_LEN_UNSET`). `none` → unset. Same units; negative dropped. |
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
| `direction` | `direction` (`css_direction`): `ltr`/`rtl`; unknown → unset. Text-direction hint for the layout engine. |
| `tab-size` | `tab_size` (number of spaces, 0 unset): a bare integer ≥ 1 and ≤ 64; units (`px`, `%`) dropped. |
| `font-variant` | `font_variant` (`css_font_variant`): `normal`/`small-caps`; extended variants (`all-small-caps`, `petite-caps`, …) dropped |
| `hyphens` | `hyphens` (`css_hyphens`): `none`/`manual`/`auto`; unknown dropped |
| `user-select` | `user_select` (`css_user_select`): `none`/`text`/`all`/`auto`; unknown dropped |
| `caret-color` | `caret_color` (0xRRGGBB or `CSS_LEN_AUTO` for `auto`, or -1 unset): color of the text-input caret |
| `appearance` | `appearance` (`css_appearance`): `auto`/`none`; unknown dropped |
| `pointer-events` | `pointer_events` (`css_pointer_events`): `auto`/`none`; unknown dropped |
| `background-repeat` | `bg_repeat` (`css_bg_repeat`): `repeat`/`no-repeat`/`repeat-x`/`repeat-y`/`space`/`round`; unknown dropped |
| `background-size` | `bg_size` (`css_bg_size`): `auto`/`cover`/`contain`; `<length>`/`<percentage>` dropped |
| `background-clip` | `bg_clip` (`css_bg_clip`): `border-box`/`padding-box`/`content-box`/`text`; unknown dropped |
| `background-origin` | `bg_origin` (`css_bg_origin`): `padding-box`/`border-box`/`content-box`; unknown dropped |
| `background-attachment` | `bg_attachment` (`css_bg_attachment`): `scroll`/`fixed`/`local`; unknown dropped |
| `isolation` | `isolation` (`css_isolation`): `auto`/`isolate`; unknown dropped |
| `contain` | `contain` (bitmask `CSS_CONTAIN_*`): `none`/`strict`/`content`/space‑separated `size` `layout` `style` `paint`; unknown tokens ignored |
| `content-visibility` | `content_visibility` (`css_content_visibility`): `visible`/`auto`/`hidden`; unknown dropped |
| `image-rendering` | `image_rendering` (`css_image_rendering`): `auto`/`pixelated`/`crisp-edges`; unknown dropped |
| `color-scheme` | `color_scheme` (`css_color_scheme`): `normal`/`light`/`dark`; first keyword in `"light dark"` wins; unknown dropped |
| `accent-color` | `accent_color` (0xRRGGBB or `CSS_LEN_AUTO` for `auto`, or -1 unset): colour of form‑control accents |
| `print-color-adjust` | `print_color_adjust` (`css_print_color_adjust`): `economy`/`exact`; unknown dropped |
| `forced-color-adjust` | `forced_color_adjust` (`css_forced_color_adjust`): `auto`/`none`; unknown dropped |
| `mix-blend-mode` | `mix_blend_mode` (`css_mix_blend`): `normal`/`multiply`/`screen`/`overlay`/`darken`/`lighten`/`color-dodge`/`color-burn`/`difference`/`exclusion`/`hue`/`saturation`/`color`/`luminosity`; unknown dropped |
| `object-fit` | `object_fit` (`css_object_fit`): `fill`/`contain`/`cover`/`none`/`scale-down`; unknown dropped |
| `list-style-position` | `list_style_pos` (`css_list_pos`): `inside`/`outside`; unknown dropped |
| `font-kerning` | `font_kerning` (`css_font_kerning`): `auto`/`normal`/`none`; unknown dropped |
| `text-rendering` | `text_rendering` (`css_text_rendering`): `auto`/`optimizeSpeed`/`optimizeLegibility`/`geometricPrecision`; unknown dropped |
| `font-stretch` | `font_stretch` (`css_font_stretch`): `normal`/`condensed`/`expanded`/`ultra‑condensed`/`extra‑condensed`/`semi‑condensed`/`semi‑expanded`/`extra‑expanded`/`ultra‑expanded`; unknown dropped |
| `resize` | `resize` (`css_resize`): `none`/`both`/`horizontal`/`vertical`; unknown dropped |
| `scroll-behavior` | `scroll_behavior` (`css_scroll_behavior`): `auto`/`smooth`; unknown dropped |
| `touch-action` | `touch_action` (`css_touch_action`): `auto`/`none`/`manipulation`; unknown dropped |
| `overscroll-behavior` | `overscroll_behavior` (`css_overscroll`): `auto`/`contain`/`none`; unknown dropped |
| `backface-visibility` | `backface_visibility` (`css_backface`): `visible`/`hidden`; unknown dropped |

#### Layout / box decoration (Hito 23b-7)

These resolve into `css_style` like the box model: **not inherited** (read from the
element's own resolved style). The `css` module only resolves the *values*; how far
each is honoured at paint time is the presentation layer's job and is staged across
later milestones. Insets/`z-index`/`order` reuse the `CSS_LEN_*` sentinels.

| Property | css_style field(s) → value/clamp |
| :-- | :-- |
| `position` | `position` (`css_position`): `static`/`relative`/`absolute`/`fixed`/`sticky`; unknown dropped (unset) |
| `top`, `right`, `bottom`, `left`; `inset` shorthand | `inset_top/right/bottom/left` (`CSS_LEN_UNSET`/`CSS_LEN_AUTO`/signed px; `em`×16; `calc()` of same; `%` dropped). `inset` expands 1–4 values (CSS order; a `calc()` value survives the shorthand split — see *`calc()`* below). |
| `z-index` | `z_index` (signed, clamped `[−CSS_LEN_MAX, CSS_LEN_MAX]`; `auto` → unset) |
| `box-sizing` | `box_sizing` (`css_box_sizing`): `content-box`/`border-box`; unknown dropped |
| `border`, `border-top/right/bottom/left` | uniform/per-side shorthand: classifies each token as a width (px/`thin`=1/`medium`=3/`thick`=5), a `style` keyword, or a color, and sets the matching `border_*_{width,style,color}` for the affected side(s). Only the parts present are set (omitted longhands stay unset — no initial-value reset). |
| `border-width`, `border-style`, `border-color` | `border_*_width`/`_style`/`_color` expanded 1–4 values (CSS order all / `v h` / `t h b` / `t r b l`). Widths px ≥ 0 (or keyword); styles `css_border_style`; colors `0xRRGGBB`. |
| `border-top/right/bottom/left-width`/`-style`/`-color` | the single per-side longhand |
| `border-radius` | `border_radius` (first value, px ≥ 0; `%` dropped). Corner-by-corner / elliptical radii out of scope. |
| `box-shadow` | `shadow2_dx`/`_dy`/`_blur`/`_spread` (signed px) + `box_shadow_color` (`0xRRGGBB`/-1) + `box_shadow_inset` (1/0/-1). Single layer: ≤4 lengths in order dx, dy, blur, spread + optional color + optional `inset`; needs ≥2 lengths or dropped; `none` → explicit no-shadow; `url()` dropped |
| `outline` (+`-width`/`-style`/`-color`) | `outline_width`/`outline_style`/`outline_color` (uniform, same token classifier as `border`) |
| `outline-width` | `outline_width` (px ≥ 0, keywords `thin`=1/`medium`=3/`thick`=5, or `CSS_LEN_UNSET`). Longhand alias of the width component in the `outline` shorthand. |
| `outline-style` | `outline_style` (`css_border_style`). Longhand alias of the style component in the `outline` shorthand. |
| `outline-color` | `outline_color` (0xRRGGBB or -1). Longhand alias of the color component in the `outline` shorthand. |
| `outline-offset` | `outline_offset` (signed px, `CSS_LEN_UNSET` unset). Same length parser as box-model (`em`/`rem` ×16, `calc()`). |
| `flex-grow`, `flex-shrink` | `flex_grow`/`flex_shrink` stored ×100 (so `0.5` → 50), clamped `[0, CSS_FLEX_FACTOR_MAX]`, or -1 (unset) |
| `flex-basis` | `flex_basis` (px ≥ 0 / `CSS_LEN_AUTO` for `auto`\|`content` / `CSS_LEN_UNSET`; `%` dropped) |
| `flex` shorthand | sets `flex_grow`/`flex_shrink`/`flex_basis`: `flex: N` → N 1 0; `none` → 0 0 auto; `auto` → 1 1 auto; `initial` → 0 1 auto; up to three explicit values in order grow shrink basis |
| `order` | `order` (signed, clamped `[−CSS_LEN_MAX, CSS_LEN_MAX]`, or `CSS_LEN_UNSET`) |
| `align-items`, `align-self`, `align-content`, `justify-items` | `css_align_kw`: `stretch`/`flex-start`\|`start`/`flex-end`\|`end`/`center`/`baseline` (+`space-*` for `align-content`; +`auto` for `align-self`); unknown dropped |
| `flex-direction` | `flex_direction` (`css_flex_direction`): `row`/`row-reverse`/`column`/`column-reverse` |
| `flex-wrap` | `flex_wrap` (`css_flex_wrap`): `nowrap`/`wrap`/`wrap-reverse` |
| `grid-template-rows` | `grid_rows` (track count, like `grid-template-columns`) |
| `row-gap` | `row_gap` (px, clamped `[0, CSS_GAP_MAX]`, or -1 unset). `column-gap`/`gap` keep feeding `gap` (first token); two-value `gap` row component is set only via `row-gap`. |
| `grid-auto-flow` | `grid_auto_flow` (`css_grid_flow`): `row`/`column`; `dense` ignored |
| `grid-column`, `grid-row` | `grid_col_span`/`grid_row_span` from a `span N` value, clamped `[1, CSS_GRID_SPAN_MAX]`; line-number / named-line forms out of scope (dropped) |
| `border-collapse` | `border_collapse` (`css_border_collapse`): `collapse`/`separate`; unknown dropped |
| `border-spacing` | `border_spacing` (signed px, `CSS_LEN_UNSET` unset): the first length only (two-value h/v → only h honoured in v1); px/em/rem/0, accepts a bare non-zero number as px; clamped `[0, CSS_BORDER_SPACING_MAX]` |
| `empty-cells` | `empty_cells` (`css_empty_cells`): `show`/`hide`; unknown dropped |
| `caption-side` | `caption_side` (`css_caption_side`): `top`/`bottom`; unknown dropped |
| `table-layout` | `table_layout` (`css_table_layout`): `auto`/`fixed`; unknown dropped |

#### Visibility, overflow, cursor, text-overflow, word-break

| Property | Resolved into `css_style` | Painted? |
| :-- | :-- | :-- |
| `visibility` | `visibility` (`css_visibility`): `visible`/`hidden`/`collapse`; `collapse` (meant for table rows) has no real table-row model here, so it collapses to `hidden` | **Yes.** `hidden` skips painting the box/its content but keeps its layout space (unlike `display:none`, which removes it entirely). A nested container (flex/grid) inside a hidden box is a known v1 gap — see below. |
| `overflow`, `overflow-x`, `overflow-y` | `overflow_x`/`overflow_y` (`css_overflow`): `visible`/`hidden`/`scroll`/`auto`; `clip` maps to `hidden` (no scroll). The `overflow` shorthand sets both axes to the same value (the two-token per-axis form is out of scope — use the longhands). | **Yes** (2026-07-09). Clipping is painted for in-flow box rows (the main `paint_structured` loop, `ov_reconcile` per row) and for positioned boxes (the two-pass painter applies the same ancestor clip). The clip rect is the box's content area after padding. `text-overflow:ellipsis` with `overflow:hidden+white-space:nowrap` continues to work (pre-existing). |
| `cursor` | `cursor` (`css_cursor`): `auto`/`default`/`pointer`/`text`/`move`/`not-allowed`/`help`/`wait`/`crosshair`/`grab`/`zoom-in`/`none`; unknown dropped | **Partially.** v1 only distinguishes `pointer` (shows the existing hand cursor, on ANY element — not just links) from every other value (shows the default arrow); the rest resolve for completeness/`debug_dom` and a future milestone that loads more cursor theme shapes. Overriding a **link's** default hand cursor away (e.g. `a{cursor:default}`) is not yet honoured. |
| `text-overflow` | `text_overflow` (`css_text_overflow`): `clip`/`ellipsis` | **Yes**, but only where `white-space:nowrap` is also set (the only signal this engine has that a line is meant to stay on one row, since `overflow:hidden` clipping is not painted yet): the line truncates at the character that fits and an ellipsis is appended. Truncating mid-word is at a UTF-8 cluster boundary, not a word boundary (matches real `text-overflow`). Text from a later inline run on the *same* visual line (after the one that triggered truncation) is a known v1 gap. |
| `word-break`, `overflow-wrap`, `word-wrap` | `word_break` (`css_word_break`, **unified** — see note below): `normal`/`break-all`/`keep-all` (word-break) or `normal`/`break-word`/`anywhere` (overflow-wrap/word-wrap); a "may break" keyword from either property sets `CSS_WB_BREAK` | **Yes**, but only for the pathological case: a single word wider than the *entire* line (not just the remaining space on it — a normal wrap already handles that) is split at UTF-8 cluster boundaries into pieces that each fit, instead of overflowing the box edge unbroken. |

**word-break/overflow-wrap unification (a deliberate simplification).** Real CSS gives
`word-break: break-all` (breaks greedily, even where unnecessary) and `overflow-wrap:
break-word`/`anywhere` (breaks only as a last resort) different semantics. This engine
only models "may a long word split at all", so every keyword from either property that
requests breaking maps to the same `CSS_WB_BREAK` value; `word-break: keep-all` (CJK
line-breaking) is not modeled and falls back to `normal`.

`visibility`/`overflow_x`/`overflow_y`/`cursor` are **not inherited** (read from the
element's own resolved style, like `position`/`border`) and live on `pv_box_def`/the
box-definition tree, gated behind `caps.css` as a whole (like the rest of the box
decoration); a block that sets *only* one of these four (no other box property) still
registers a box-def entry, but box registration itself remains scoped to block-level
tags (the same scope the rest of the box model has — `cursor:pointer` on a bare inline
`<a>` does not register a box; wrap it in a block-level element, or rely on the link's
already-hand-cursor default). `text_overflow`/`word_break` **inherit** like
`white-space` (nearest ancestor wins) and live on the run (`pv_run`/`rd_block`).

### Property inventory (supported vs missing)

**Supported** (resolved into `css_style`, gated downstream as noted):

- *Color / background*: `color`, `background-color`, `background` (color only).
- *Text*: `text-align`, `font-size`, `font-weight`, `font-style`, `line-height`,
   `text-decoration`(`-line`), **`text-decoration-color`**, **`text-decoration-style`**,
   **`font-family`**, **`text-transform`**, **`font-variant`** (`small-caps`,
   **painted** 2026-07-10 as uppercase),
   **`letter-spacing`**, **`word-spacing`**, **`text-shadow`**, **`opacity`**,
   **`vertical-align`**, **`text-indent`**, **`white-space`** (wrap/no-wrap only),
   **`tab-size`** (carried; **painted** 2026-07-10 in pre/pre-wrap blocks for
   tab characters, but `pv_build`'s whitespace collapse still turns raw tabs
   into single spaces before flow sees them — the property is correct, the
   upstream collapse is a separate gap),
   **`direction`** (carried, **painted** 2026-07-10 as a record; the v1
   paint does not actually reorder inline runs RTL, it just carries the
   value downstream),
   **`text-overflow`** (painted with `white-space:nowrap`), **`word-break`**/
   **`overflow-wrap`**/**`word-wrap`** (unified, painted for the single-word-wider-
   than-the-line case),
   **`list-style-position`** (inside/outside; carried, **painted** 2026-07-10
   as a record — the v1 engine already prepends the marker, so inside/outside
   differ only when the marker layout differs, which a v1 follow-up will
   refine),
   **`hyphens`**, **`user-select`**, **`caret-color`** (**painted** 2026-07-10:
   tints the text caret of a focused form control; `auto`/unset keeps the theme
   caret; gated by `caps.css`).
- *Layout / box*: `display`, `gap`(`grid-gap`/`column-gap`), `justify-content`,
   `grid-template-columns` (`repeat()`/`minmax()`-aware track **count**), `margin`
   (+longhands), `padding`(+longhands), `width`, `min-width`, `max-width`,
   `height`, `min-height`, `max-height` (**all four painted** 2026-07-10:
   `width`/`max-width` are the existing cap, the new four are `min-width`/`height`/
   `min-height`/`max-height` applied at `open_box`/`close_top_box`),
   `aspect-ratio` (carried on `pv_box_def`, **painted** 2026-07-10: a fixed
   aspect ratio sizes the box's height from its width when no explicit
   height is given) — all length-valued properties among these accept `calc()`
   and the math functions `min()`/`max()`/`clamp()` (see *Math functions* below).
- *Logical properties* (2026-07-10, physical mapping — see *Logical properties*
   below): `margin-inline`(`-start`/`-end`), `margin-block`(`-start`/`-end`),
   `padding-inline`(`-start`/`-end`), `padding-block`(`-start`/`-end`),
   `inset-inline`(`-start`/`-end`), `inset-block`(`-start`/`-end`),
   `inline-size`, `block-size`, `min-inline-size`, `max-inline-size`,
   `min-block-size`, `max-block-size`.
- *Alignment shorthands* (2026-07-10): **`place-items`** (→ `align-items` +
   `justify-items`), **`place-content`** (→ `align-content` + `justify-content`),
   **`place-self`** (→ `align-self`; the justify-self half has no engine slot and
   is ignored — documented simplification, like `list-style`'s ignored tokens).
   **`gap`/`grid-gap`** accept the two-value form `gap: <row> <col>` (row feeds
   `row-gap`, column feeds `gap`; the one-value form keeps its prior semantics).
- *Font shorthand* (2026-07-10): **`font`** — `[style] [variant] [weight]
   size[/line-height] family`, e.g. `font: italic bold 16px/1.5 sans-serif`.
   Emits `font-style`/`font-variant`/`font-weight`/`font-size`/`line-height`/
   `font-family` through the same interpreters as the longhands. `size` and
   `family` are both required (per CSS); system keywords (`caption`/`menu`/…)
   and unparseable sizes drop the whole shorthand (fail closed).
- *Layout / box decoration* (**Hito 23b-7**): **`position`** (+`top`/`right`/
   `bottom`/`left`/`inset`/`z-index`), **`box-sizing`**, **`border`**(/`-width`/
   `-style`/`-color`, per-side + longhands), **`border-radius`**, **`box-shadow`**
   (single-layer, **outset + inset both painted** 2026-07-10 — inset is the
   same painter clipped to inside the border box with the offset translating
   toward the opposite edge),
   **`outline`**(+`-width`/`-style`/`-color` longhands), **`outline-offset`**,
   **`flex`**(/`-grow`/`-shrink`/`-basis`), **`order`**,
   **`align-items`/`align-self`/`align-content`/`justify-items`**, **`flex-direction`**,
   **`flex-wrap`**, **`grid-template-rows`**, **`row-gap`**, **`grid-auto-flow`**,
    **`grid-column`/`grid-row`** (`span N`),
   **`border-collapse`**, **`border-spacing`**, **`empty-cells`**,
   **`caption-side`**, **`table-layout`.
   **Painted** since the CSS layout expansion
   batch: `flex-wrap` (multi-line wrapping), `row-gap` (distinct grid/flex-wrap cross
   gap), `align-items`/`align-self` (flex row cross-axis only). Still value-resolved
   only (not yet painted): `border`/`box-shadow` rendering, `align-content`,
   grid item placement (`grid-column`/`grid-row: span N`), grid cross-axis alignment.
   `position`/`z-index` are **painted** (2026-07-09): positioned boxes are painted in
   a two-pass pass (negative z-index behind in-flow, z-index≥0 above in-flow), each
   with overflow clipping applied from ancestors.
- *Lists*: `list-style-type`, `list-style` (type token only).
- *Float* (**spec/float.md**): **`float`** (`left`/`right`/`none`), **`clear`**
  (`left`/`right`/`both`/`none`). Consumed by the painter as side-by-side float bands
  that nest in the open box stack; see spec/float.md for the v1 scope.
- *Visibility / overflow / cursor / interaction*: **`visibility`** (painted: skip-draw, space
   reserved), **`overflow`**/**`overflow-x`**/**`overflow-y`** (painted: clips
   in-flow rows and positioned boxes to ancestor `overflow:hidden` rects;
   2026-07-09; the `clip` keyword resolves to the same clipping as `hidden`),
   **`cursor`** (painted: `pointer` shows the hand cursor on any
   element, the rest resolve but paint as the default arrow),
   **`appearance`**, **`pointer-events`** (**wired** 2026-07-10: `none` on a
   box or an ancestor box removes the element from hit-testing — links under it
   do not hover/click, `cursor` does not resolve there; rides the box-def tree
   like `cursor`, so it is caps.css-gated by construction),
   **`content-visibility`** (**wired** 2026-07-10: `hidden` folds into the box's
   `visibility` at page_view time — contents skip painting but keep their layout
   space, the same documented simplification as `visibility: collapse`; `auto`/
   `visible` have no effect).
- *At-rules / cascade*: `@media` (subset: `prefers-color-scheme`, `screen`/`print`/
  `all`, `min/max-width`), `!important`.
- *Values*: **`calc()`** (`+`/`-`/`*`/`/`, parens, dimensionally checked) and
  **`var()`**/custom properties (a page-global `--name` table, `CSS_VAR_MAX_DEPTH`
  bounded), composing with each other and every shorthand tokenizer.

(Properties in **bold** are the Hito 23b-7 batch. The `css` module resolves their
values; honouring the rest at paint time — full flex/grid sizing, out-of-flow
positioning beyond Stage 2 — is staged across later milestones.)

**Not yet supported** (dropped / fail closed unless noted), highest cosmetic value
first:

- *Box decoration, finer grain*: corner-by-corner / elliptical `border-radius`,
  multi-layer `box-shadow`, `box-shadow` blur/spread *rendering* (resolved but not
  yet painted), `border-image`. The single-layer outset + inset **is** painted
  since 2026-07-10; multi-layer / per-corner radii / blur quality remain gaps.

**Parsed/resolved, but carried in `css_style` without an active paint effect
(2026-07-10 audit).** These properties are accepted by the parser, cascade
through the same pipeline, and ride the wire to the GUI — but the v1
engine does not act on them yet. Listed here so a reader of `css_style`
does not assume every field is wired; when a later milestone wires one
of them, the field already has the value ready. Grouped by family:

- *Background image / decoration*: `background-image`/`background-repeat`/
  `background-size`/`background-clip`/`background-origin`/`background-
  attachment` (no CSS `background-image` painting — `url()` is dropped
  by doctrine, and CSS-painted gradients would need a compositing path
  the flat painter does not have).
- *Compositing / containment*: `isolation`, `contain` (no stacking-context /
  paint-tree partitioning in the v1 painter). `content-visibility` left this
  list 2026-07-10 (`hidden` folds into `visibility`, see above).
- *Color/meta*: `color-scheme`, `print-color-adjust`, `forced-color-adjust`,
  `object-fit`, `accent-color` (no checkbox/radio widgets to tint yet —
  form controls collapse to text boxes/buttons), `appearance`,
  `mix-blend-mode`. `image-rendering`, `caret-color` and `pointer-events`
  left this list 2026-07-10 (painted/wired, see above). `image-rendering:
  pixelated`/`crisp-edges` selects the nearest-neighbour scaling filter when
  the painter blits a decoded image (needs `caps.images` to matter, gated by
  `caps.css` like the rest of the author presentation). The `image-rendering`
  filter, the `caret-color` tint and the `pointer-events` hit-test skip are
  unit-tested through rd_build and compile-verified in the GUI painter, but not
  yet visually verified in a live session (headless export has no images-on
  flag, no focused caret and no pointer).
- *Interaction*: `hyphens`, `user-select`, `resize`, `scroll-behavior`,
  `touch-action`, `overscroll-behavior`, `backface-visibility`,
  `font-kerning`, `text-rendering`, `font-stretch`.
- *Flex/grid extras (parsed, not yet placed)*: `align-content`,
  `justify-items`, `grid-template-rows`, `grid-auto-flow`,
  `grid-column`/`grid-row` `span N` (every grid item still occupies one
  cell — `span N` is resolved but not honored in the layout engine).
- *Table properties*: `border-collapse`, `border-spacing`, `empty-cells`,
  `caption-side`, `table-layout` (no proper table layout; the engine
  flattens `<table>` to per-cell block-defs, so these would only
  matter when a real table layout is added).
- *Out of v1 engine scope*: `text-decoration-thickness` (resolved; the
  painter uses the `deco_thick` field but currently collapses it to the
  default 1.0 in v1), `vertical-align` length / `top` / `middle` /
  `bottom` keywords (only `sub`/`super`/`baseline` are painted), and
  `position: sticky` scroll pinning (fail-closed to `relative`).
- *Positioning, finer grain*: text **wrapping around** a single float (a float
   followed by non-floated content — v1 float bands are self-contained rows; see
   spec/float.md), line-number / named grid placement (only `span N` is
   resolved), `position: sticky` scroll pinning. `overflow` clipping and
   `z-index` negative stacking **are** painted since 2026-07-09.
- *Backgrounds beyond a solid color*: `background-image`/gradients (and any
  `url()` — by doctrine, never fetched), `background-position`.
- *Transforms / filters / transitions*: `transform`, `filter`, `transition`,
  `animation`, `@keyframes`.
- *Text, finer grain*: `text-transform: full-width`, `letter-spacing`/`text-indent`
  in `%`/viewport units, `text-decoration-thickness`,
  `vertical-align` length/`top`/`middle`/`bottom`, `white-space` whitespace
  *preservation* (only the wrap distinction is consumed), the greedy-vs-last-resort
  distinction between `word-break: break-all` and `overflow-wrap: break-word`
  (unified to one behaviour), `text-overflow: ellipsis` on a line with more inline
  content after the truncation point (v1 gap), `writing-mode`.
- *Flex/grid, finer grain*: `align-content` (parsed/resolved, not yet painted —
  only `align-items`/`align-self` reach the painter), grid per-item placement
  (`grid-column`/`grid-row: span N` are resolved but not yet honoured — every grid
  item still occupies exactly one cell), `fr` weights/named tracks (every counted
  track — `repeat()`/`minmax()`-aware since this batch — still lays out as an
  equal-width column), `justify-items` (parsed/resolved, not yet painted).
  **Flex-direction `*-reverse`** and **`flex-wrap: wrap-reverse`** were the last
  `*-reverse` reversal gap: `row-reverse` reverses the visual order of items on
  the main axis; `column-reverse` reverses the visual stack of items (first item
  at bottom, last at top); `wrap-reverse` reverses the cross-axis line order
  (first line at bottom, last at top). All three are now painted (Hito 2026-07-09).
- *Selectors*: `:not()`/`:is()`/`:where()`/`:has()`, `:first-of-type`/of-type
  family, `:empty`, `:target`, `:lang()`, all pseudo-elements `::` (dropped, fail
  closed). Sibling combinators `+`/`~` and the pseudo-class subset above **are**
  supported since Hito 23b-9; dynamic pseudos (`:hover`/`:focus`/`:active`) parse
  but never match (no interactive re-cascade yet), `:visited` never matches by
  Zero-Knowledge design.
- *Values*: `%`/viewport units anywhere (`calc()`/plain lengths alike), `url()`
  anything, `@import`/`@font-face`. `calc()` and `var()`/custom properties **are**
  supported (see below) — a simplified, bounded, non-executing subset.

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
all feed them, inline winning). **Lengths** accept `px`, a bare `0`, `em`/`rem` (×16 px,
the engine's base font), and `calc()` of the same (see *`calc()`* above); `%`/`vw`/`vh`
and other units are **dropped** (fail closed — they need a containing-block width the
parser does not have). They are **not inherited** (a box
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

**Container layout params (Hito 23b-2, extended by the CSS layout expansion batch).**
`gap` / `justify-content` / `grid-template-columns` / **`flex-wrap`** / **`row-gap`** /
**`align-items`** resolve through the **same cascade** as the other properties (so a
`<style>` rule, a compound/id selector, and an inline `style=` all feed them, inline
winning). They are **not inherited** (they describe the flex/grid container element
itself, so the caller reads them from that element's resolved style, not up the
ancestor chain); **`align-self`** is the mirror-image ITEM property (like the Stage 3
flex-grow/-shrink/-basis/order), read from the element one step more inner on the walk.
page_view consumes them to parameterize the flex/grid layout, which is **always
applied and not gated by `caps.css`** (doctrine: "Layout != estilo de autor" —
geometry is structure, it opens no socket and leaks nothing). Only author *colors*
stay behind `caps.css`. See `spec/box_tree.md` for how `layout_flex`/`layout_grid`
consume `flex-wrap` (multi-line packing by flex basis), `row-gap` (falls back to
`gap` when unset — `has_row_gap` defaults to 0 under zero-init, so every caller that
predates the property keeps its exact prior geometry), and `align-items`/`align-self`
(cross-axis offset within a flex line; grid cross-axis alignment is still deferred).

**Custom properties + `var()` (CSS layout expansion).** A `--name: value` declaration
anywhere in the stylesheet — any rule, any `@media` block — feeds one flat,
**page-global** table (`collect_custom_props`, up to `CSS_MAX_CUSTOM_PROPS` (64)
entries, each name/value bounded like every other token here to `CSS_TOK_MAX`; a
later declaration of the same name overwrites an earlier one). This is a
deliberate simplification of real CSS's cascade-scoped custom properties, chosen
because it covers the overwhelmingly common `:root { --x: ... }` pattern without
needing per-element scoping. `var(--name)` / `var(--name, fallback)` is resolved
(`resolve_var`) when a declaration's value is interpreted: a hit substitutes the
custom property's (recursively resolved) value; a miss uses the fallback if given,
else the **whole declaration fails** (matches real CSS: an unresolvable `var()`
with no fallback makes the property invalid, not some improvised value). Lookups
recurse at most `CSS_VAR_MAX_DEPTH` (4) deep, so a chain or a self-reference
(`--a: var(--a)`) fails the declaration instead of recursing/expanding unboundedly
(anti-DoS — the bound is per-lookup, not per-document, so a hostile stylesheet
cannot use it to burn CPU). An inline `style=` sees BOTH its own custom properties
and the stylesheet's (its own win on a name collision, being closer to the use
site). `var()` never phones home: whatever text it substitutes still flows through
the same property interpreter, so e.g. `background: var(--evil)` where
`--evil: url(...) #112233` still extracts the colour (`0x112233`) while the URL is dropped — same as a literal `background: url(...) #112233`.

**`calc()` (CSS layout expansion).** A length value (anything that flows through
`interp_len`: `margin`/`padding`/`width`/`max-width`/`top`/`right`/`bottom`/`left`/
`inset`/`text-indent`, and transitively `flex-basis`/border-width/outline-width/
text-shadow and box-shadow offsets) accepts `calc(...)`: a small recursive-descent
evaluator (`calc_eval`) over `+`, `-`, `*`, `/` and parens, with the same units
`interp_len` already understands (`px`, `em`/`rem` ×16, bare `0`) — no `%`/viewport
units (this engine has no containing-block/viewport width to resolve them
against, so `calc()` cannot reach further than a plain length already could).
Dimensionally checked like real `calc()`: `+`/`-` require both sides to be the
same "shape" (both lengths, or both bare numbers — `calc(10px + 5)` is invalid);
`*` requires at least one bare-number side (`calc(10px * 5px)` is invalid); `/`
requires a bare-number, non-zero divisor. A bare-number *result* (`calc(2 * 3)`,
no length anywhere) is not a valid length and fails, like any other unsupported
value. Bounded: the whole expression already lives inside one `CSS_TOK_MAX`
(64-byte) token, and `CSS_CALC_MAX_DEPTH` (8) caps parenthesis nesting.
**`calc()` composes with `var()`:** `var()` substitution happens first (on the raw
declaration text), so `calc(var(--gap) * 2)` resolves the custom property's text
into the expression before it is evaluated.

A `calc(...)` value commonly contains **internal spaces** (`calc(10px + 5px)`).
Every multi-value shorthand that could otherwise hand a naively-space-split
fragment to a calc-aware interpreter (`margin`/`padding`/`inset`, `flex`,
`border-width`/`border-style`/`border-color`, `border`/`border-<side>`/`outline`,
`text-shadow`, `box-shadow`) tokenizes via **one shared paren-aware splitter**
(`next_ws_token`, which tracks paren depth so it never splits inside a `(...)`
call) instead of each having its own ad-hoc whitespace loop — this was a real bug
caught by `/visual-review` (a `flex: 0 0 calc(100px + 120px)` silently dropped to
the shorthand's fallback share because the old per-shorthand tokenizers split the
value at the space after `100px`) and is now covered by
`test_calc_inside_shorthands`.

**Math functions `min()` / `max()` / `clamp()` (2026-07-10).** Anywhere a length
accepts `calc()` it also accepts `min(a, b, ...)`, `max(a, b, ...)` and
`clamp(lo, mid, hi)` — both as the **whole value** (`width: min(600px, 40em)`)
and **nested inside** `calc()`/each other (`calc(min(10px, 2em) * 2)`,
`clamp(1em, calc(2px + 3px), 10px)`). Each argument is a full calc expression
over the same units (`px`, `em`/`rem` ×16, bare `0`; no `%`/viewport units —
same containing-block limitation as `calc()`). Dimensional rules: every argument
of one call must have the same shape (all lengths or all bare numbers — mixing
fails the declaration); `clamp()` takes exactly three arguments and resolves to
`max(lo, min(mid, hi))` per CSS; `min()`/`max()` take 1..`CSS_MATHFN_MAX_ARGS`
(8) arguments (more fail closed). Bounded like `calc()`: the value lives inside
one `CSS_TOK_MAX` token and shares `CSS_CALC_MAX_DEPTH` for nesting — a hostile
sheet cannot recurse or expand unboundedly.

**Logical properties (2026-07-10, physical v1 mapping).** The inline/block
logical properties map to their **physical** equivalents assuming
`horizontal-tb` + LTR (the engine does not support `writing-mode`, and the
cascade interprets values before it knows the element's resolved `direction` —
a `direction: rtl` page keeps the LTR mapping; documented simplification, fail
closed nowhere): `*-inline-start` → `*-left`, `*-inline-end` → `*-right`,
`*-block-start` → `*-top`, `*-block-end` → `*-bottom`; the two-value shorthands
`margin-inline: A B` / `padding-block: A B` / `inset-inline: A B` set
start/end (one value sets both). `inline-size`/`min-inline-size`/
`max-inline-size` → `width`/`min-width`/`max-width`; `block-size`/
`min-block-size`/`max-block-size` → `height`/`min-height`/`max-height`. All
reuse the physical properties' interpreters, so `auto`, negatives (margins
only), `calc()` and the math functions behave identically; the caps.css gates
downstream are those of the mapped physical property.

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
    int          text_decoration_color;  /* 0xRRGGBB or -1 (unset) */
    int          text_decoration_style;  /* css_text_decoration_style, 0 unset */
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
    int          width, max_width, min_width;
    int          height, min_height, max_height;
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
    int          tab_size;        /* number of spaces, 0 unset */
    int          list_style;      /* css_list_style, 0 unset */
    int          direction;       /* css_direction, 0 unset */
    /* Layout / box decoration (Hito 23b-7; not inherited, value-resolution only —
     * not yet threaded through IPC nor painted; honouring staged for later milestones). */
    css_position    position;     /* CSS_POS_UNSET if absent */
    int          inset_top, inset_right, inset_bottom, inset_left; /* CSS_LEN_UNSET/AUTO/signed px */
    int          z_index;         /* signed, [-CSS_LEN_MAX, CSS_LEN_MAX], or CSS_LEN_UNSET */
    css_box_sizing  box_sizing;   /* CSS_BOXS_UNSET if absent */
    int          border_top_width, border_right_width, border_bottom_width, border_left_width; /* px>=0 / CSS_LEN_UNSET */
    css_border_style border_top_style, border_right_style, border_bottom_style, border_left_style;
    int          border_top_color, border_right_color, border_bottom_color, border_left_color; /* 0xRRGGBB / -1 */
    int          border_radius;   /* px>=0, or CSS_LEN_UNSET */
    int          shadow2_dx, shadow2_dy, shadow2_blur, shadow2_spread; /* box-shadow px (signed) */
    int          box_shadow_color;/* 0xRRGGBB, or -1 (none/unset) */
    int          box_shadow_inset;/* 1 inset, 0 outset, -1 unset */
    int          outline_width;   /* px>=0, or CSS_LEN_UNSET */
    css_border_style outline_style;
    int          outline_color;   /* 0xRRGGBB, or -1 */
    int          outline_offset;  /* signed px, CSS_LEN_UNSET (unset) */
    int          flex_grow, flex_shrink; /* stored x100 (0.5 -> 50), [0,CSS_FLEX_FACTOR_MAX], or -1 */
    int          flex_basis;      /* px>=0 / CSS_LEN_AUTO / CSS_LEN_UNSET */
    int          order;           /* signed, [-CSS_LEN_MAX, CSS_LEN_MAX], or CSS_LEN_UNSET */
    css_align_kw    align_items, align_self, align_content, justify_items;
    css_flex_direction flex_direction; /* CSS_FD_UNSET if absent */
    css_flex_wrap   flex_wrap;    /* CSS_FW_UNSET if absent */
    int          grid_rows;       /* grid-template-rows track count, or 0 (unset) */
    int          row_gap;         /* px, [0, CSS_GAP_MAX], or -1 (unset) */
    css_grid_flow   grid_auto_flow; /* CSS_GF_UNSET if absent */
    int          grid_col_span, grid_row_span; /* span N, [1, CSS_GRID_SPAN_MAX], or 0 (unset) */
    css_float    float_side;      /* CSS_FLOAT_UNSET if absent */
    css_clear    clear;           /* CSS_CLEAR_UNSET if absent */
    css_visibility  visibility;   /* CSS_VIS_UNSET if absent */
    css_overflow    overflow_x, overflow_y; /* CSS_OF_UNSET if absent */
    css_cursor      cursor;       /* CSS_CUR_UNSET if absent */
    css_text_overflow text_overflow; /* CSS_TO_UNSET if absent */
    css_word_break  word_break;   /* CSS_WB_UNSET if absent; unifies word-break/overflow-wrap */
    css_border_collapse border_collapse; /* CSS_BCOL_UNSET if absent */
    int             border_spacing;  /* px, CSS_LEN_UNSET if absent */
    css_empty_cells empty_cells;     /* CSS_EC_UNSET if absent */
    css_caption_side caption_side;   /* CSS_CS_UNSET if absent */
    css_table_layout table_layout;   /* CSS_TL_UNSET if absent */
    css_font_variant font_variant;   /* CSS_FV_UNSET if absent */
    css_hyphens      hyphens;        /* CSS_HY_UNSET if absent */
    css_user_select  user_select;    /* CSS_US_UNSET if absent */
    int              caret_color;    /* 0xRRGGBB or -1 if absent */
    css_appearance   appearance;     /* CSS_AP_UNSET if absent */
    css_pointer_events    pointer_events;     /* CSS_PE_UNSET if absent */
    css_bg_repeat         bg_repeat;          /* CSS_BGR_UNSET if absent */
    css_bg_size           bg_size;            /* CSS_BGS_UNSET if absent */
    css_bg_clip           bg_clip;            /* CSS_BGC_UNSET if absent */
    css_bg_origin         bg_origin;          /* CSS_BGO_UNSET if absent */
    css_bg_attachment     bg_attachment;      /* CSS_BGA_UNSET if absent */
    css_isolation         isolation;          /* CSS_ISO_UNSET if absent */
    int                   contain;            /* bitmask CSS_CONTAIN_*; 0 = unset/none */
    css_content_visibility content_visibility; /* CSS_CV_UNSET if absent */
    css_image_rendering   image_rendering;    /* CSS_IR_UNSET if absent */
    css_color_scheme      color_scheme;       /* CSS_CSH_UNSET if absent */
    int                   accent_color;       /* 0xRRGGBB, CSS_LEN_AUTO, or -1 unset */
    css_print_color_adjust print_color_adjust; /* CSS_PCA_UNSET if absent */
    css_forced_color_adjust forced_color_adjust; /* CSS_FCA_UNSET if absent */
    css_mix_blend        mix_blend_mode;          /* CSS_MB_UNSET if absent */
    css_object_fit       object_fit;              /* CSS_OFI_UNSET if absent */
    css_list_pos         list_style_pos;          /* CSS_LP_UNSET if absent */
    css_font_kerning     font_kerning;            /* CSS_FK_UNSET if absent */
    css_text_rendering   text_rendering;          /* CSS_TR_UNSET if absent */
    css_font_stretch     font_stretch;            /* CSS_FS_UNSET if absent */
    css_resize           resize;                  /* CSS_RS_UNSET if absent */
    css_scroll_behavior  scroll_behavior;         /* CSS_SB_UNSET if absent */
    css_touch_action     touch_action;            /* CSS_TA_UNSET if absent */
    css_overscroll       overscroll_behavior;     /* CSS_OS_UNSET if absent */
    css_backface         backface_visibility;     /* CSS_BF_UNSET if absent */
} css_style;

typedef enum css_position {
    CSS_POS_UNSET = 0, CSS_POS_STATIC, CSS_POS_RELATIVE,
    CSS_POS_ABSOLUTE, CSS_POS_FIXED, CSS_POS_STICKY
} css_position;
typedef enum css_box_sizing { CSS_BOXS_UNSET = 0, CSS_BOXS_CONTENT, CSS_BOXS_BORDER } css_box_sizing;
typedef enum css_border_style {
    CSS_BST_UNSET = 0, CSS_BST_NONE, CSS_BST_HIDDEN, CSS_BST_SOLID, CSS_BST_DASHED,
    CSS_BST_DOTTED, CSS_BST_DOUBLE, CSS_BST_GROOVE, CSS_BST_RIDGE, CSS_BST_INSET, CSS_BST_OUTSET
} css_border_style;
typedef enum css_flex_direction {
    CSS_FD_UNSET = 0, CSS_FD_ROW, CSS_FD_ROW_REVERSE, CSS_FD_COLUMN, CSS_FD_COLUMN_REVERSE
} css_flex_direction;
typedef enum css_flex_wrap { CSS_FW_UNSET = 0, CSS_FW_NOWRAP, CSS_FW_WRAP, CSS_FW_WRAP_REVERSE } css_flex_wrap;
typedef enum css_align_kw {
    CSS_AK_UNSET = 0, CSS_AK_AUTO, CSS_AK_STRETCH, CSS_AK_START, CSS_AK_END,
    CSS_AK_CENTER, CSS_AK_BASELINE, CSS_AK_SPACE_BETWEEN, CSS_AK_SPACE_AROUND, CSS_AK_SPACE_EVENLY
} css_align_kw;
typedef enum css_grid_flow { CSS_GF_UNSET = 0, CSS_GF_ROW, CSS_GF_COLUMN } css_grid_flow;

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
typedef enum css_float {
    CSS_FLOAT_UNSET = 0, CSS_FLOAT_NONE, CSS_FLOAT_LEFT, CSS_FLOAT_RIGHT
} css_float;
typedef enum css_clear {
    CSS_CLEAR_UNSET = 0, CSS_CLEAR_NONE, CSS_CLEAR_LEFT, CSS_CLEAR_RIGHT, CSS_CLEAR_BOTH
} css_clear;
typedef enum css_visibility {
    CSS_VIS_UNSET = 0, CSS_VIS_VISIBLE, CSS_VIS_HIDDEN, CSS_VIS_COLLAPSE
} css_visibility;
typedef enum css_overflow {
    CSS_OF_UNSET = 0, CSS_OF_VISIBLE, CSS_OF_HIDDEN, CSS_OF_SCROLL, CSS_OF_AUTO
} css_overflow;
typedef enum css_cursor {
    CSS_CUR_UNSET = 0, CSS_CUR_AUTO, CSS_CUR_DEFAULT, CSS_CUR_POINTER, CSS_CUR_TEXT,
    CSS_CUR_MOVE, CSS_CUR_NOT_ALLOWED, CSS_CUR_HELP, CSS_CUR_WAIT, CSS_CUR_CROSSHAIR,
    CSS_CUR_GRAB, CSS_CUR_ZOOM_IN, CSS_CUR_NONE
} css_cursor;
typedef enum css_text_overflow { CSS_TO_UNSET = 0, CSS_TO_CLIP, CSS_TO_ELLIPSIS } css_text_overflow;
typedef enum css_word_break { CSS_WB_UNSET = 0, CSS_WB_NORMAL, CSS_WB_BREAK } css_word_break;
typedef enum css_text_decoration_style {
    CSS_TDS_UNSET = 0, CSS_TDS_SOLID, CSS_TDS_DOUBLE, CSS_TDS_DOTTED,
    CSS_TDS_DASHED, CSS_TDS_WAVY
} css_text_decoration_style;
typedef enum css_direction { CSS_DIR_UNSET = 0, CSS_DIR_LTR, CSS_DIR_RTL } css_direction;
typedef enum css_border_collapse { CSS_BCOL_UNSET = 0, CSS_BCOL_COLLAPSE, CSS_BCOL_SEPARATE } css_border_collapse;
typedef enum css_empty_cells { CSS_EC_UNSET = 0, CSS_EC_SHOW, CSS_EC_HIDE } css_empty_cells;
typedef enum css_caption_side { CSS_CS_UNSET = 0, CSS_CS_TOP, CSS_CS_BOTTOM } css_caption_side;
typedef enum css_table_layout { CSS_TL_UNSET = 0, CSS_TL_AUTO, CSS_TL_FIXED } css_table_layout;
typedef enum css_font_variant { CSS_FV_UNSET = 0, CSS_FV_NORMAL, CSS_FV_SMALL_CAPS } css_font_variant;
typedef enum css_hyphens { CSS_HY_UNSET = 0, CSS_HY_NONE, CSS_HY_MANUAL, CSS_HY_AUTO } css_hyphens;
typedef enum css_user_select { CSS_US_UNSET = 0, CSS_US_NONE, CSS_US_TEXT, CSS_US_ALL, CSS_US_AUTO } css_user_select;
typedef enum css_appearance { CSS_AP_UNSET = 0, CSS_AP_AUTO, CSS_AP_NONE } css_appearance;
typedef enum css_pointer_events { CSS_PE_UNSET = 0, CSS_PE_AUTO, CSS_PE_NONE } css_pointer_events;
typedef enum css_bg_repeat { CSS_BGR_UNSET = 0, CSS_BGR_REPEAT, CSS_BGR_NO_REPEAT, CSS_BGR_REPEAT_X, CSS_BGR_REPEAT_Y, CSS_BGR_SPACE, CSS_BGR_ROUND } css_bg_repeat;
typedef enum css_bg_size { CSS_BGS_UNSET = 0, CSS_BGS_AUTO, CSS_BGS_COVER, CSS_BGS_CONTAIN } css_bg_size;
typedef enum css_bg_clip { CSS_BGC_UNSET = 0, CSS_BGC_BORDER_BOX, CSS_BGC_PADDING_BOX, CSS_BGC_CONTENT_BOX, CSS_BGC_TEXT } css_bg_clip;
typedef enum css_bg_origin { CSS_BGO_UNSET = 0, CSS_BGO_PADDING_BOX, CSS_BGO_BORDER_BOX, CSS_BGO_CONTENT_BOX } css_bg_origin;
typedef enum css_bg_attachment { CSS_BGA_UNSET = 0, CSS_BGA_SCROLL, CSS_BGA_FIXED, CSS_BGA_LOCAL } css_bg_attachment;
typedef enum css_isolation { CSS_ISO_UNSET = 0, CSS_ISO_AUTO, CSS_ISO_ISOLATE } css_isolation;
#define CSS_CONTAIN_NONE   0
#define CSS_CONTAIN_SIZE   1
#define CSS_CONTAIN_LAYOUT 2
#define CSS_CONTAIN_STYLE  4
#define CSS_CONTAIN_PAINT  8
typedef enum css_content_visibility { CSS_CV_UNSET = 0, CSS_CV_VISIBLE, CSS_CV_AUTO, CSS_CV_HIDDEN } css_content_visibility;
typedef enum css_image_rendering { CSS_IR_UNSET = 0, CSS_IR_AUTO, CSS_IR_PIXELATED, CSS_IR_CRISP_EDGES } css_image_rendering;
typedef enum css_color_scheme { CSS_CSH_UNSET = 0, CSS_CSH_NORMAL, CSS_CSH_LIGHT, CSS_CSH_DARK } css_color_scheme;
typedef enum css_print_color_adjust { CSS_PCA_UNSET = 0, CSS_PCA_ECONOMY, CSS_PCA_EXACT } css_print_color_adjust;
typedef enum css_forced_color_adjust { CSS_FCA_UNSET = 0, CSS_FCA_AUTO, CSS_FCA_NONE } css_forced_color_adjust;
typedef enum css_mix_blend { CSS_MB_UNSET = 0, CSS_MB_NORMAL, CSS_MB_MULTIPLY, CSS_MB_SCREEN, CSS_MB_OVERLAY, CSS_MB_DARKEN, CSS_MB_LIGHTEN, CSS_MB_COLOR_DODGE, CSS_MB_COLOR_BURN, CSS_MB_DIFFERENCE, CSS_MB_EXCLUSION, CSS_MB_HUE, CSS_MB_SATURATION, CSS_MB_COLOR, CSS_MB_LUMINOSITY } css_mix_blend;
typedef enum css_object_fit { CSS_OFI_UNSET = 0, CSS_OFI_FILL, CSS_OFI_CONTAIN, CSS_OFI_COVER, CSS_OFI_NONE, CSS_OFI_SCALE_DOWN } css_object_fit;
typedef enum css_list_pos { CSS_LP_UNSET = 0, CSS_LP_OUTSIDE, CSS_LP_INSIDE } css_list_pos;
typedef enum css_font_kerning { CSS_FK_UNSET = 0, CSS_FK_AUTO, CSS_FK_NORMAL, CSS_FK_NONE } css_font_kerning;
typedef enum css_text_rendering { CSS_TR_UNSET = 0, CSS_TR_AUTO, CSS_TR_OPTIMIZE_SPEED, CSS_TR_OPTIMIZE_LEGIBILITY, CSS_TR_GEOMETRIC_PRECISION } css_text_rendering;
typedef enum css_font_stretch { CSS_FS_UNSET = 0, CSS_FS_NORMAL, CSS_FS_CONDENSED, CSS_FS_EXPANDED, CSS_FS_ULTRA_CONDENSED, CSS_FS_EXTRA_CONDENSED, CSS_FS_SEMI_CONDENSED, CSS_FS_SEMI_EXPANDED, CSS_FS_EXTRA_EXPANDED, CSS_FS_ULTRA_EXPANDED } css_font_stretch;
typedef enum css_resize { CSS_RS_UNSET = 0, CSS_RS_NONE, CSS_RS_BOTH, CSS_RS_HORIZONTAL, CSS_RS_VERTICAL } css_resize;
typedef enum css_scroll_behavior { CSS_SB_UNSET = 0, CSS_SB_AUTO, CSS_SB_SMOOTH } css_scroll_behavior;
typedef enum css_touch_action { CSS_TA_UNSET = 0, CSS_TA_AUTO, CSS_TA_NONE, CSS_TA_MANIPULATION } css_touch_action;
typedef enum css_overscroll { CSS_OS_UNSET = 0, CSS_OS_AUTO, CSS_OS_CONTAIN, CSS_OS_NONE } css_overscroll;
typedef enum css_backface { CSS_BF_UNSET = 0, CSS_BF_VISIBLE, CSS_BF_HIDDEN } css_backface;
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
#define CSS_BORDER_W_MAX  CSS_LEN_MAX       /* px clamp for border/outline widths */
#define CSS_FLEX_FACTOR_MAX 100000          /* clamp for flex-grow/shrink (stored x100) */
#define CSS_GRID_SPAN_MAX 1000              /* clamp for grid-column/-row span N */

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
    /* Hito 23b-9 (all optional; zero/NULL = unknown = structural/sibling
     * selectors fail closed): */
    int nth;                          /* 1-based index among element siblings, 0 unknown */
    int nsib;                         /* total element siblings incl. self, 0 unknown */
    const struct css_element *prev;   /* previous element sibling, or NULL */
} css_element;
```

The caller supplies as much of the chain as it has (bounded is fine: a missing deep
ancestor only means a descendant selector against it fails to match — fail closed).
`attrs`/`nattrs` may be empty (`NULL`/`0`): an attribute selector against an element
with no attribute list simply does not match. The Hito 23b-9 fields are equally
optional: `nth`/`nsib` = 0 makes `:first-child`/`:nth-child(...)`-style selectors
not match, `prev` = NULL makes `+`/`~` not match — never a mis-match. Pure,
allocates nothing, re-entrant.

**Dado** un `css_element` con `nth=2, nsib=4` y `prev` apuntando a su hermano
anterior — **cuando** se resuelve una hoja con `li:nth-child(even){...}` o
`li + li{...}` — **entonces** ambas reglas aplican al elemento. **Dado** el mismo
elemento con `nth=0`/`prev=NULL` (el llamador no pudo poblarlos) — **cuando** se
resuelve — **entonces** ninguna de las dos aplica (fail closed, jamás un falso
positivo).

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

- Selectors, still dropped (fail closed): `:not()`/`:is()`/`:where()`/`:has()`,
  the of-type family, `:empty`/`:target`/`:lang()`, and every pseudo-element
  (`::before`/`::after`/legacy `:before`). Supported: descendant (` `), child
  (`>`), adjacent (`+`) and general (`~`) sibling combinators (Hito 23b-9, up to
  `CSS_MAX_COMPOUNDS` compounds); **attribute** selectors `[attr]`, `[attr=v]`,
  `~=`, `|=`, `^=`, `$=`, `*=` (with the `i`/`s` case flag, Hito 23b-4, up to
  `CSS_MAX_ATTR_SEL` per compound); the **pseudo-class subset** of Hito 23b-9
  (`:link`/`:any-link`/`:visited`/`:hover`-family/`:root`/`:first-child`/
  `:last-child`/`:only-child`/`:nth-child()`/`:nth-last-child()`/`:checked`/
  `:disabled`/`:enabled`, up to `CSS_MAX_PSEUDO_SEL` per compound).
- Inheritance/`initial`/`inherit`/`unset` keywords (caller does inheritance;
  these keywords are ignored).
- The author box model `margin`/`padding`/`width`/`max-width` **is now resolved through the
  cascade** (Hito 23b-3) and applied (gated by `caps.css`): horizontal insets, an optional
  width cap, `margin: 0 auto` centering, and a top/bottom margin override; all four (plus
  `calc()` of them) are supported. Still out of scope: `border` (values resolved, not yet
  painted), `box-sizing`, vertical `padding-top/bottom` application, `%`/viewport units, and
  nested box composition (see *Box model* above). `display:flex|grid` *parameters*
  (`gap`/`justify-content`/`grid-template-columns`/`flex-wrap`/`row-gap`/`align-items`/
  `align-self`) are resolved through the cascade (Hito 23b-2) **and painted** (the CSS layout
  expansion batch: multi-line flex wrapping, distinct grid/flex-wrap row-gap, flex row
  cross-axis alignment). Still out of scope: grid cross-axis alignment, `align-content`, grid
  per-item placement (`grid-column`/`grid-row: span N` resolved, not yet honoured), and named/
  `auto`/`fr`-weighted grid tracks (every counted track — `repeat()`/`minmax()`-aware — still
  lays out as an equal-width column).
- `url()` anything, `@import`/`@font-face`/other `@`-rules. `!important` **is** honored (Hito
  23b-4): the suffix is stripped and the declaration raised to a higher cascade tier (was
  previously dropped). `@media` is supported (subset above); `not`/unknown features fail
  closed. **`calc()`** (`+`/`-`/`*`/`/`, parens, dimensionally checked, composes with `var()`)
  and **`var()`**/custom properties (a page-global `--name` table) **are** supported — see
  the *`calc()`*/*Custom properties* sections above for the exact bounded, non-executing
  subset.
- `position` (relative/absolute/sticky) and other layout/box properties — deferred to
  the layout milestone (Hito 23b-2); `@media print` *rendering* into the PDF is deferred
  (print-only rules are correctly excluded from the screen view today).
- `text-decoration` (and `text-decoration-line`) **is** supported for the line keywords
  `underline`/`overline`/`line-through`/`none` (Hito 23b-5; gated by `caps.css`).
  **`text-decoration-color`** and **`text-decoration-style`** are also supported
  (resolved as separate `css_style` fields). Still out of scope: `text-decoration-thickness`
  (dropped), and text-decoration propagation semantics (our flat model resolves the nearest
  ancestor that set it, like `color`).
- **`font-family`, `text-transform`, `letter-spacing`, `word-spacing`, `text-shadow`,
  `opacity`, `vertical-align`, `text-indent`, `white-space`, `list-style-type`/`list-style`**
  **are** supported (Hito 23b-6; see *Property inventory* and the *Properties* table for the
  exact subset and fail-closed rules). Still out of scope within them: exact font matching
  (only generic buckets), `text-shadow` blur/multi-layer, `%`/viewport `letter-spacing`/
  `text-indent`, `vertical-align` lengths/`top`/`middle`/`bottom`, and `white-space`
  whitespace *preservation* (only the wrap distinction is consumed). The full "Not yet
  supported" list (borders, `position`, transforms, gradients, …) is in *Property inventory*.
