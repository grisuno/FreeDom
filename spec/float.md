# spec: float — `float:left` / `float:right` side-by-side bands (+ `clear`)

> **Why.** The classic two-column web (Slashdot, forums, blogs of that era) is built
> on `float`: a sidebar `float:left`, a main column beside it, a `clear:both` footer
> below. Freedom had no `float`, so those columns **stacked vertically** — the sidebar,
> then the main content, then the footer, one under the other; the page looked broken.
> A wrapping `position:relative` background panel around the columns then paints its
> background **behind nothing** (its content is elsewhere), leaving the page background
> showing as grey stripes. This milestone lays consecutive floated siblings **side by
> side** and, crucially, **nests the float band inside the open box stack**, so the
> wrapping panel stays open and paints its background behind the columns.

This is layout **structure** (like flex/grid), applied regardless of `caps.css`, so
the two-column shape appears even with author colors off. It opens no socket, reads
no file, runs no script: it consumes inert, already-fuzzed `css` values and measures
geometry.

## 1. CSS layer (`[[css]]`)

Two new whitelisted, **non-inherited** properties (read from the element's own
resolved style, like the box model):

| Property | `css_style` field | Values (else the declaration is dropped, fail closed) |
| :-- | :-- | :-- |
| `float` | `float_side` (`css_float`) | `none` / `left` / `right` |
| `clear` | `clear` (`css_clear`) | `none` / `left` / `right` / `both` |

```c
typedef enum css_float { CSS_FLOAT_UNSET = 0, CSS_FLOAT_NONE, CSS_FLOAT_LEFT, CSS_FLOAT_RIGHT } css_float;
typedef enum css_clear { CSS_CLEAR_UNSET = 0, CSS_CLEAR_NONE, CSS_CLEAR_LEFT, CSS_CLEAR_RIGHT, CSS_CLEAR_BOTH } css_clear;
```

An unknown keyword drops the declaration (the property stays unset). No `url(`, no
`@`-rule, nothing to phone home: these are pure keyword enums.

## 2. page_view layer (`[[page_view]]`)

`resolve_context` walks a text run's ancestors. Two things are resolved:

- **`float_id` + `float_side`** come from the **nearest floated self-or-ancestor
  block** (the block element whose own `float_side` is left/right). Its identity is
  registered in a document-order registry (a `float_id`, separate from `cont_id`), so
  every run inside one floated element shares one id and the painter can group them
  into one column. `float_side` is that element's side. A run with no floated ancestor
  gets `float_id = -1`, `float_side = 0`.
- **`float_clear`** comes from the run's **own leaf block** element's `clear` (like the
  vertical margins `box_mt`/`box_mb`): the block that clears is the one that must drop
  below the preceding floats.

These are **structure**, carried on `pv_run` regardless of `caps.css`, exactly like
`cont_id`/`block_id`.

## 3. IPC (`[[tab]]`) + render_doc (`[[render_doc]]`)

`write_view`/`read_view` serialize the **3 new int32s** (`float_side`, `float_id`,
`float_clear`) **in the same order on both sides** (the desync gotcha,
`[[freedom-render-pipeline-ipc]]`), as one contiguous block right after `cont_item`,
via a new `pv_set_float` setter. `rd_build` copies them **always** (structure, like
`cont_*`/`block_id`), so the two-column layout is applied whether or not author CSS is
enabled. `dom_debug` prints `float=left|right`, `float_id=N`, `clear=...` after
`cont=` when set.

## 4. Painter (`[[browser_ui]]` `layout_doc` + a pure packer)

### 4.1 Pure packing helper (`[[flex_layout]]`)

```c
fx_status fx_float_pack(const double *width, const int *side, size_t n,
                        double avail, double gap, double *out_x);
```

Packs `n` float items into one band: `side[i] == 0` (left) items advance a left cursor
from `0` rightward in document order; `side[i] == 1` (right) items advance a right
cursor from `avail` leftward in document order. `out_x[i]` is each item's x offset from
the content start (clamped to `>= 0`; the band does **not** wrap in v1). Pure, no
allocation, no I/O. `n == 0` is a no-op.

### 4.2 Band detection + nesting

In `layout_doc`, a **float band** is a maximal run of consecutive blocks each with
`float_id >= 0`, stopping at the first non-floated block or a block whose
`float_clear != none`. For a band `[i, j)`:

1. **Nest, don't break the box.** Compute the band's **common box** — the innermost
   box that is an ancestor (via the `pv_box_def` parent chain) of *every* block in the
   band. `reconcile_boxes` opens that box (and its ancestors), so a wrapping
   `position:relative` background panel is **opened in flow and paints its background
   behind the columns**. (Flex/grid containers still `close_all_boxes`; floats do not —
   that is the whole point.)
2. **Group** the band's blocks by `float_id` into items (document order); each item's
   width is its first block's author `box_w` (an explicit `width`), and items without a
   width split the leftover evenly.
3. **Pack** the item widths + sides with `fx_float_pack` inside the common box's content
   rect (`[ctx_left, ctx_left + ctx_w)`).
4. **Flow** each item's blocks into its column (a fresh sub-state, like the flex
   per-item pass), translate the rows to `(base_top + column_x, column_y)`, and set the
   band height to the tallest column. A column's block formatting context is a real
   BFC, so a **flex/grid container nested inside a float column** (e.g. a data `<table>`
   in Slashdot's floated story body) is laid out by `layout_container` at the **column
   width**, exactly as the top-level loop does — not flowed run-by-run as plain lines
   (which dropped every table cell onto its own row, collapsing a 2-column table to a
   1-column list). The container's grid runs carry a per-column `x_off`; the row
   translation therefore **adds** `ctx_left + column_x` (symmetric with the box shift)
   instead of assigning it, so grid column offsets survive. A plain flowed row has
   `x_off = 0` in a column, so the add is identical to the old assignment.
5. Advance `cur_top` past the band; the next block (e.g. the `clear:both` footer)
   reconciles the box stack normally and flows below.

## 5. Security posture (non-negotiable)

- **No network, no execution.** Inert presentation data from the fuzzed `css` cascade;
  the painter only measures geometry. Opens no socket, reads no file, runs no script.
- **Structure, applied always.** Float is layout, like flex/grid: carried by
  `render_doc` regardless of `caps.css`. Author *colors* stay gated; the two-column
  *shape* is structure.
- **Fail closed / bounded.** Unknown `float`/`clear` keywords drop the declaration. The
  band is bounded by the existing `BT_MAX_CHILDREN` item cap and `RC_BOX_STACK_MAX`
  nesting cap; the packer clamps every x to `>= 0` and never wraps or allocates.
- **Default byte-identical.** A page with no `float` has every float field at its unset
  default (`float_id = -1`), so band detection never fires and the render is
  byte-identical to before.

## 6. Given-When-Then

- **Given** `<div style="float:left;width:180px">nav</div>
  <div style="float:left;width:400px">main</div>` **when** rendered, **then** the two
  divs lay **side by side** (nav's rows at x≈0, main's rows at x≈180+gap), not stacked.
- **Given** a `float:right` sidebar and a `float:left` main in document order, **when**
  packed, **then** the sidebar sits at the **right** edge and the main at the left,
  regardless of document order.
- **Given** a `position:relative;background:#fff` panel wrapping the floated columns,
  **when** laid out, **then** the panel box is **opened in flow** (not sent to the page
  bottom) and its background paints **behind** the columns — no grey stripes.
- **Given** a `clear:both` footer after the floats, **when** laid out, **then** the band
  ends and the footer flows **below** the tallest column at full width.
- **Given** a page with **no** `float`, **when** rendered, **then** `float_id == -1` on
  every run and the layout is **byte-identical** to before.
- **Given** `float` on a page rendered with author CSS **off** (`caps.css` off), **when**
  rendered, **then** the columns still lay side by side (structure), only the author
  colors are absent.

## 6b. Text flows BESIDE a single float (v3, 2026-08-10)

> **Why.** v1's headline limitation — "a float followed by non-floated content does not
> flow that content beside the float" — was the single largest measured divergence from
> Firefox in the whole renderer (`tests/parity/pages/float-beside.html`: 1.77× too tall,
> and every sidebar/infobox/pull-quote page collapses into one tall stack). A second bug
> hid inside the same probe: a **lone `float:right`** painted at the far **left**.

### 6b.1 The lone-float box bug (`band_shared_box`)

`band_common_box` returns the innermost box that is an ancestor **or self** of every
block in the band. For a band of exactly ONE float that is the float's **own** box, and
opening it as the band's *shared* context put the float's background/padding in the
**parent's** coordinates — so a `float:right` sidebar painted its box at the parent's
left edge while its text was packed to the right.

The band's shared context must be a box that cannot belong to a single float:

- **≥ 2 distinct `float_id`s** in the band: the common box is shared by two different
  floats, so it is a genuine wrapper. Unchanged — this is what keeps a wrapping
  `position:relative` panel open in flow and painting behind the columns (§4.2).
- **exactly 1** `float_id`: every box below the parent's already-open stack belongs to
  that one float and must be opened **inside its column**. The shared context is the
  deepest box **already open** on the parent state that lies on the band's common path
  (`-1` when none). A wrapper that also contains later, non-floated content is still
  opened — by that content's own reconcile, as any other block's box is.

### 6b.2 Line-box exclusion (`fx_float_insets`, pure)

CSS 2.1 §9.5: a float does not change the block's box, it **shortens the line boxes**
that overlap it. So the float keeps its column, `cur_top` does **not** jump past it, and
each following line box asks how much room the float leaves at its own `y`:

```c
typedef struct fx_float_rect { double top, bottom, edge; int side; } fx_float_rect;

fx_status fx_float_insets(const fx_float_rect *r, size_t n, double y, double h,
                          double avail, double *out_l, double *out_r);
```

`edge` is the **inner** content edge the float steals: for `side == 0` (left) the x just
past its right margin, for `side == 1` (right) the x of its left margin. A rect
contributes only when it vertically overlaps the half-open band `[y, y + h)`, which is
what makes a line **return to the full width** the moment it clears the float's bottom.
`out_l` is the max left `edge` over overlapping left rects, `out_r` is `avail` minus the
min right `edge`; both are clamped to `>= 0` and to leave at least
`FX_FLOAT_MIN_LINE` (1px) of room, so a hostile float wider than the container can never
produce a negative or zero line width (fail-open geometry, never an error). Pure, no
allocation, no I/O.

**Dado** un `float:left` de 220px con `bottom = 60`
**cuando** se pide el inset de una línea en `y = 10, h = 20`
**entonces** `out_l = 220`, `out_r = 0` — la línea empieza pasado el float.

**Dado** la misma exclusión
**cuando** la línea está en `y = 70` (ya pasó el `bottom`)
**entonces** `out_l = 0` — la línea recupera el ancho completo, como en Firefox.

**Dado** un `float:right` cuyo `edge` es `avail - 176`
**entonces** `out_r = 176` y `out_l = 0`.

### 6b.3 Wiring (`layout_doc` / `open_line` / `flow_text`)

- A band of **one item on one row** registers an exclusion instead of advancing
  `cur_top`: `top = base_top`, `bottom = base_top + column height`, `edge` from the
  packer's `outx` + the item width, `side` from the float. `cur_top` returns to
  `base_top`.
- Multi-item / multi-row bands keep advancing `cur_top` exactly as before, so the
  two-column era layout (Slashdot, 960.gs) is byte-identical.
- `open_line` recomputes the line's insets for its own `cur_top` and starts `pen_x` at
  the left inset; `flow_text` wraps against `content_w - right_inset`. Both read the
  cached `float_l`/`float_r` on `rc_state`, refreshed once per line.
- Exclusions are **dropped** (and `cur_top` advanced to the tallest `bottom`) by: a
  block whose own `clear` is set, the start of a new float band, a flex/grid container,
  and the end of the document. That is what keeps a `clear:both` footer below the
  columns and what makes the page tall enough when the float outlives its text.
- An exclusion whose `bottom <= cur_top` is expired and discarded.
- Bounded: `RC_FLOAT_MAX` (8) live exclusions; a ninth is dropped (fail-open — content
  overlaps a float rather than disappearing).

**Default byte-identical:** a page with no `float` registers nothing, `float_l`/`float_r`
stay 0, and `open_line`/`flow_text` behave exactly as before.

## 7. v1 limitations (documented, honest)
- **Float items' own nested box decoration is not composed** inside a column (same v1
  limit as flex/grid containers): a bordered `.story` inside a floated `.main` paints
  its text but not its border. The wrapping panel's background *does* paint (nesting).
- **`clear` granularity collapsed.** `clear:left`/`right`/`both` all end the band; the
  cleared block flows below the whole band (no per-side float context in v1).
- **Width-less floats split leftover evenly** (no shrink-to-fit content measure).
- **Nesting depth** bounded by `RC_BOX_STACK_MAX`; band item count by `BT_MAX_CHILDREN`.

## 7b. Band wrap + percentage widths (v2, Hito 32)

v1's "the band does not wrap" broke every 960.gs-era site (Slashdot): consecutive
`.grid_24 { width:99.8%; float:left }` items packed side by side into one row, and with
the `%` width dropped by the cascade each item degraded to an equal share — the page
became unreadable one-word columns. v2 fixes both, keeping the packer pure:

- **`fx_float_pack_wrap(width, side, n, avail, gap, out_x, out_row)`** — same cursor
  discipline as v1 plus a greedy row break: an item that no longer fits between the two
  cursors starts a **new row** (cursors reset; `out_row[i]` reports each item's row).
  An item wider than `avail` alone still gets a clamped `x = 0` and consumes its row
  (fail-open geometry, never an error). `fx_float_pack` (v1, single row) remains; both
  share one implementation.
- **Dado** dos floats `width:99.8%` consecutivos, **cuando** se empaqueta con wrap,
  **entonces** cada uno ocupa su PROPIA fila (`out_row` = 0, 1) en `x = 0` — apilados.
- **Dado** cuatro floats que sí caben juntos, **entonces** comparten la fila 0 con las
  mismas x que daba v1.
- `layout_float_band` lays each row's columns independently; the band height is the
  **sum over rows** of each row's tallest column.
- **Percentage widths** resolve at layout time: a run/box carries `box_w_pct`
  (per-mille, `0` = none) next to the px cap `box_w`; the effective cap is
  `bx_width_cap(box_w_px, box_w_pct, avail)` (`[[box_style]]`, pure; both set ⇒ the
  tighter wins). The cascade parses `width`/`max-width` percentages into
  `css_style.width_pct`/`max_width_pct` (`[[css]]`, per-mille, fail-closed on junk);
  every other `%` length still fails closed.

## 7c. Holy-grail floats: founder margins + column content width (2026-09-07)

> **Why.** The other classic two-column idiom — a `width:100%` float wrapping the
> article plus a `width:320px` rail pulled beside it with `margin-left:-320px`
> (Slashdot's `.main-wrap`/`.rail-right`) — rendered as a full-width article with
> the rail **below** it (`tests/parity/pages/slashdot-cols.html`: Freedom 1465px
> vs Firefox 2049px, score 13.41; real `slashdot.html` col_mae 0.38). Two summed
> breaches, both measurable against Firefox geometry (rail at top=8, left=664 in
> a 984 container; article 664 wide, not 984):
>
> 1. **The packer placed border boxes, not margin boxes.** CSS 2.1 §9.5 positions
>    floats by their OUTER (margin) edges: a 320px rail with `margin-left:-320px`
>    has a ZERO-width outer box, so it still fits on the row after a 100%-wide
>    float — and its border renders one margin to the LEFT of its packed slot
>    (`border_x = packed_outer_x + margin_left`, signed). The band packed
>    `952 + 320 > 952` and wrapped the rail onto its own row below.
> 2. **Column text wrapped at the column width, not the content width.** The flat
>    path flows text at the open box's inner width (`rc_box_context` + the block's
>    own cap/centring); the float-band column flowed at the raw column width, so
>    `.main-content{margin-right:320px}` narrowed its box to 632px while its text
>    still wrapped at 952px.

### 7c.1 Founder margins (`[[page_view]]` → `[[render_doc]]` → `[[tab]]`)

The margins the packer needs are the FLOAT FOUNDER's own (the element whose
`float_side` founded the `float_id` group) — not the nearest-hbox insets on the
run (those belong to descendants: `.main-content`'s `margin-right:320px` is
INTERIOR to `.main-wrap` and must never inflate its outer width), and not the
group's common box (same reason). `page_view` holds the founder's resolved style
in hand when it detects the float, so it stamps all four `<length-percentage>`
halves — `float_ml/float_ml_pct/float_mr/float_mr_pct`, signed ints, per-mille
pct — onto `pv_cont_info`, `pv_run` (via `pv_set_float`), and `rd_block`
(structure, carried regardless of `caps.css`, like `float_id`; resolved against
the band width by the painter with `bx_lp_px`). A run with no floated ancestor
carries zeros. `write_view`/`read_view` serialize them appended to block B (same
order both sides, `[[freedom-render-pipeline-ipc]]`); `dom_debug` prints them as
`fml=`/`fmr=` when nonzero.

### 7c.2 Margin-aware packing (pure, `[[flex_layout]]`)

```c
fx_status fx_float_pack_m(const double *width, const int *side,
                          const double *ml, const double *mr, size_t n,
                          double avail, double gap,
                          double *out_x, size_t *out_row);
```

`width[i]` is the BORDER width; `ml[i]`/`mr[i]` the founder margins in px
(signed, same basis — the caller resolved `%` already). Packs the OUTER widths
(`width + ml + mr`, clamped `>= 0`, so a negative margin NARROWS the slot and a
positive one widens it — both per CSS 2.1 §9.5 outer edges) with the v2 cursor
discipline + greedy row wrap, then reports the BORDER x (`packed_outer_x + ml`).
Zero margins are exactly `fx_float_pack_wrap` (locked by test). The lone-float
exclusion edge becomes the outer right (`x + ml + width + mr` for a left float;
symmetric from the right) — with zero margins identical to before.

### 7c.3 Column content width (`[[browser_ui]]` `layout_float_band`)

Each item's blocks flow at the flat-path width: inside an open box, the box's
inner width via `rc_box_context` (the block's own width cap and `margin:0 auto`
centring still apply through `bx_place(0,0,…)` — re-applying insets would
double-count the box's); at column top level, the block's own `bx_place`
(insets + cap + centring, exactly as `layout_doc`). `si.indent_px`/`si.bg_w`
follow the same rule, so rows report the content width and `text-align` centres
inside the box, not the column. With no inner boxes and no author caps the
computation answers the raw column width — byte-identical.

### 7c.4 Given-When-Then

- **Given** `.main-wrap{width:100%;float:left}` + `.rail-right{width:320px;
  float:left;margin-left:-320px}` in a 952 band, **when** packed, **then** one
  row (`out_row` 0, 0), x = 0 and 632 — the rail's border fills the gap the
  article's `margin-right:320px` reserves (Firefox: left=664 of 984).
- **Given** two 500px floats with `margin-right:100px` on the first in a 1000
  band, **when** packed, **then** two rows — a positive margin WIDENS the slot.
- **Given** zero founder margins, **when** packed with `_m`, **then** byte-equal
  to `fx_float_pack_wrap` (same x, same rows).
- **Given** text inside `.main-content{margin-right:320px}` in a 952 float
  column, **when** flowed, **then** lines wrap at 632, not 952.
- **Given** a page with no float margins, **when** rendered, **then**
  `layout-diff` byte-identical (founder margins are all zero; the inner-width
  computation answers the column width).

### 7c.5 Out-of-flow blocks do not split bands (2026-09-07)

Stage 2d already skips out-of-flow-subtree blocks from FLOW (they are placed by
the positioner), but the float-band detector still ended the band on them: an
empty run riding an absolute box (`float_id = -1`, e.g. a comment bubble's
rotated square inside a rail list item) cut the rail's band on every list item,
so each link laid out as its own full-width band below the previous instead of
one compact rail column. A block that leaves the flow (`block_leaves_flow`,
same predicate) is now skipped by the band EXTENSION scan, by item GROUPING
(flanking same-id groups merge across it), and by the per-item flow loop (which
also closes the double-paint of non-empty OOF content inside float columns —
the tanda-21 absolute-dropdown class). Bands that share no OOF block behave
exactly as before.

- **Given** rail list items each carrying an absolute bubble run, **when** the
  band is detected, **then** the items form ONE band (one rail column), not one
  band per item.
- **Given** a page with no OOF block inside a float band, **when** rendered,
  **then** `layout-diff` byte-identical.

### 7c.5 Out-of-flow blocks do not split bands (2026-09-07)

Stage 2d already skips out-of-flow-subtree blocks from FLOW (they are placed by
the positioner), but the float-band detector still ended the band on them: an
empty run riding an absolute box (`float_id = -1`, e.g. a comment bubble's
rotated square inside a rail list item) cut the rail's band on every list item,
so each link laid out as its own full-width band below the previous instead of
one compact rail column. A block that leaves the flow (`block_leaves_flow`,
same predicate) is now skipped by the band EXTENSION scan, by item GROUPING
(flanking same-id groups merge across it), and by the per-item flow loop (which
also closes the double-paint of non-empty OOF content inside float columns —
the tanda-21 absolute-dropdown class). Bands that share no OOF block behave
exactly as before.

- **Given** rail list items each carrying an absolute bubble run, **when** the
  band is detected, **then** the items form ONE band (one rail column), not one
  band per item.
- **Given** a page with no OOF block inside a float band, **when** rendered,
  **then** `layout-diff` byte-identical.

## 7d. PROPOSED (red): nested pull-up floats — the rail below (2026-09-07)

> **Status: SPEC ONLY (red state: `slashdot` 20.70).** Everything in §7c is
> correct and validated, yet the real rail still renders BELOW the articles
> (col_mae 0.30 = 12 of 20.7 points; ~1200px of the height gap). This section
> records the measured root cause and the committed design. Implementing it is
> the next architectural milestone, not a bugfix: it restructures the float
> subsystem (recursive columns), so it runs the full SDD cycle on its own.

### 7d.1 Measured root cause (not a hypothesis)

`slashdot.html`'s rail (`aside#slashboxes.rail-right`, `width:320px`,
`margin-left:-320px`, founder margins cross the pipeline since §7c.1) never
shares a band with the articles, for TWO summed structural reasons measured in
`--dump-dom`/`--dump-layout`:

1. **Cross-band:** the articles are inner floats (`article.grid_24`, one group
   per story) in their own bands; the rail's blocks (`float #67`, `#68`, …)
   arrive dozens of bands later. Sequential bands can never place the rail at
   container top: §7c's packer only pulls WITHIN a band, and the probe
   (`slashdot-cols` 13.41 → 11.03) works precisely because it has NO inner
   floats (one shared band). A pagination band (`« Newer/Older »`, group #6,
   full-width outer) rides WITH the rail's band — so whole-band pull-up would
   teleport the pagination to page top: bands must SPLIT pull-up items
   (outer≤0) from sequential ones.
2. **Nested founders:** the rail's content carries TWO founder levels —
   `#67` blocks stamped with the aside's own `-320` margin (direct content)
   beside `#68` (poll section, an INNER float, no margins). `page_view`
   stamps only the NEAREST founder (`got_float` stops at the first), so the
   GUI cannot see that both live inside the aside's pulled column. Inner
   bands pack at page width instead of the 320px column.

Consequence for the score: stories now wrap at Firefox-exact widths (§7c.3
proven to 1–3px on `story-chain`), bodies break line-for-line with the
reference, yet the page stays +1480px: rail-below (~1200) + pre-existing
broken nav (~250, "nav tosco" debt) + boundary whitespace (pre-existing).

### 7d.2 Design: outermost-founder columns with pull-up placement

Runs/blocks carry the OUTERMOST float founder alongside the nearest:
`float_oid` (group id, -1 = nearest IS outermost), `float_oside`,
`float_oml/oml_pct/omr/omr_pct` (signed halves, for the outer column's pack) —
appended to IPC block B, same order both sides
(`[[freedom-render-pipeline-ipc]]`). `page_view`'s ancestor walk already visits
every ancestor: instead of stopping at the nearest float it keeps the last one
(identical cost). Blocks with `oid == -1` (or `oid == float_id`) behave
EXACTLY as today (gate-safe by construction: stories, probes, all 20 examples
byte-identical).

Layout (`layout_doc` + `layout_float_band`, reused, not forked):

1. **Defer:** bands whose groups carry `oid != id` do not lay out inline;
   their block ranges collect into a deferred column keyed by `oid` (bounded
   map, ≤8 live columns; a ninth flushes the oldest — fail-open, content
   overlaps instead of vanishing, same doctrine as `RC_FLOAT_MAX`).
2. **Flush:** at the next non-float, non-deferred block (or EOF — footer with
   `clear:both` is the canonical trigger), each deferred column lays its
   inner bands with `layout_float_band` at the COLUMN width (320, not page
   width), stacked vertically inside the column (inner bands keep their own
   row discipline; inner margins still apply within).
3. **Pull-up placement:** the column's outer packing uses the OUTER founder's
   margins (`oml/omr`): outer≤0 takes no room (fits any row, §7c.2 rule). Its
   vertical anchor is the in-flow top tracked since §7d.3: the column lands at
   container top beside earlier content instead of below it. `cur_top` becomes
   `max(cur_top, column_bottom)` — page flow never rewinds.
4. **Exclusion:** after placing a pulled column, register its rect as a float
   exclusion (existing `fx_float_rect` machinery), so FOLLOWING content wraps
   below/around it, and LATER fragments of the same column (same x-range)
   stack beneath earlier ones via the overlap rule — no new state.
   Earlier content is untouched (per CSS, later floats never move earlier
   content — this is what makes the design safe to interleave with the
   sequential loop).

### 7d.3 The anchor (measured, not invented)

The pull-up needs the containing block's content top. It is tracked, not
configured: `layout_doc` remembers the bottom of the last non-whitespace,
in-flow, non-OOF block (nav "Search Slashdot" text is the live instance on
slashdot; whitespace-only and float bands never move it; `clear` resets it).
Unset anchor (probe: everything floats) degrades EXACTLY to current behavior
(same-band pack proceeds). No box registry change is required: the anchor is
one scalar plus a per-shared-box direct-mapped table (16 slots, first-wins —
container tops do not move) for nested containers; miss ⇒ old path.

### 7d.4 Given-When-Then (red; implement to green)

- **Given** `slashdot.html`, **when** rendered, **then** the rail paints
  top-right beside story 1 (rail rows at x≈632 from y≈440, as Firefox:
  `aside.rail-right top=8 left=672 of 984`), stories keep their exact widths,
  and the score drops from 20.70 toward ~8 (col_mae 0.30 → <0.10 with no page
  worse).
- **Given** `slashdot-cols` (no inner floats, anchor unset), **when**
  rendered, **then** byte-identical to §7c (11.03): the new path never fires.
- **Given** a page with no `oid != id` block, **when** rendered, **then**
  `layout-diff` byte-identical (the deferred map stays empty).
- **Given** 9 simultaneous pulled columns, **when** rendered, **then** the
  ninth degrades to sequential flow (bounded map, fail-open, content never
  lost).

## 8. Errors

No new status codes. `css`/`page_view`/`render_doc`/`tab` keep their existing tables;
malformed author CSS was already dropped fail-closed by `css` before reaching here.
`fx_float_pack` returns `FX_ERR_NULL_ARG` (NULL with `n > 0`) / `FX_ERR_RANGE`
(`n > FX_MAX_ITEMS`, negative `avail`/`gap`) and writes nothing on error.
