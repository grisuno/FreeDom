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
   band height to the tallest column.
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

## 7. v1 limitations (documented, honest)

- **No text wrap around a single float.** A float followed by *non-floated* content does
  not flow that content beside the float; the band is a self-contained row and the next
  non-floated block clears below it. The side-by-side win covers the common case where
  every column is floated (the two-column era layout).
- **Float items' own nested box decoration is not composed** inside a column (same v1
  limit as flex/grid containers): a bordered `.story` inside a floated `.main` paints
  its text but not its border. The wrapping panel's background *does* paint (nesting).
- **`clear` granularity collapsed.** `clear:left`/`right`/`both` all end the band; the
  cleared block flows below the whole band (no per-side float context in v1).
- **Width-less floats split leftover evenly** (no shrink-to-fit content measure).
- **No percentage widths** (the cascade already drops `%` for box-model lengths).
- **Nesting depth** bounded by `RC_BOX_STACK_MAX`; band item count by `BT_MAX_CHILDREN`.

## 8. Errors

No new status codes. `css`/`page_view`/`render_doc`/`tab` keep their existing tables;
malformed author CSS was already dropped fail-closed by `css` before reaching here.
`fx_float_pack` returns `FX_ERR_NULL_ARG` (NULL with `n > 0`) / `FX_ERR_RANGE`
(`n > FX_MAX_ITEMS`, negative `avail`/`gap`) and writes nothing on error.
