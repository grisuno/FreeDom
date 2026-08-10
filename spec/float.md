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

## 8. Errors

No new status codes. `css`/`page_view`/`render_doc`/`tab` keep their existing tables;
malformed author CSS was already dropped fail-closed by `css` before reaching here.
`fx_float_pack` returns `FX_ERR_NULL_ARG` (NULL with `n > 0`) / `FX_ERR_RANGE`
(`n > FX_MAX_ITEMS`, negative `avail`/`gap`) and writes nothing on error.
