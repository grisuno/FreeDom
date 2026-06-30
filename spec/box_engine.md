# spec: box engine (Hito 23b-8) — honor the box layout/decoration resolved by Hito 23b-7

> The CSS cascade (`[[css]]`, Hito 23b-7) already resolves ~40 layout/decoration
> values into `css_style` (`include/css.h:223-252`), but **nothing consumes them**:
> they never leave `css_style`. This hito threads the box-decoration subset
> through the render pipeline and paints it. It is delivered in steps so each is a
> green §3 cycle:
>
> - **Step A (DELIVERED):** thread the box-decoration values
>   `css_style → pv_run → IPC (tab.c) → rd_block`, plus a `block_id` that groups the
>   runs of one block-level box. No painting → default render byte-identical.
> - **Step B+C (DELIVERED):** in `gui/browser_ui.c` `layout_doc`, group consecutive
>   `rd_block`s sharing a `block_id` into a block box (`open_box`/`close_box`),
>   reserve its border+padding geometry, and record an `rc_box` rect; a new
>   `paint_box_decoration` draws box-shadow / background fill / the four borders /
>   outline behind the rows, on screen and in the PDF path. The existing hbox/
>   `bx_place` already insets content by the box padding, so the box engine only adds
>   the border. Verified visually (`--author-css --download-pdf`): three cards
>   (border+bg+padding, border+drop-shadow, border+outline) render correctly and the
>   non-author-CSS path stays byte-identical (boxes vanish).
>   **v1 limitations:** square corners (`border-radius` threaded, not yet rounded);
>   dashed/dotted collapse to solid; a box broken by an image/input/flex container;
>   no nested-box composition; `box-sizing` resolved but border-box width math not yet
>   subtracted from an explicit author `width`.
>
> - **Step D (DELIVERED):** nested box composition — boxes become a TREE (`parent_id`
>   + a box-definition list), so a child box composes inside its parent instead of
>   splitting it, and text-less wrapper boxes paint. See below.
>
> - **Stage 2 (DELIVERED):** `position` (relative / absolute / fixed) + `z-index`
>   stacking pass. The values were already resolved into `pv_box_def.position` /
>   `inset_*` / `z_index` (`include/page_view.h:193-195`); Stage 2 threads them
>   through the layout and paints out-of-flow boxes in the correct stacking order.
>   `position:sticky` falls closed to `relative` (no scroll hooks in the render).
>   See below.
>
> Out of scope for this hito (own follow-ups): flex/grid per-item sizing, `%`/viewport
> units, corner-by-corner radius, multi-layer shadow, layout invalidation ("dirty
> flag"), `position:sticky` (no scroll hooks). Those `css_style` fields stay
> resolved-but-unconsumed.

## Security posture (non-negotiable)

- **No network, no execution.** This is inert presentation data already resolved by
  the fuzzed `css` cascade; the box engine only measures geometry and paints. It
  opens no socket, reads no file, runs no script.
- **Author presentation, gated.** A border/box-shadow/padding can reshape content
  (e.g. a tiny `width` + huge padding), so the box-decoration values are gated
  behind `caps.css` in `render_doc`, exactly like author colors and the Hito 23b-3
  box model. `block_id` is **structure** (identity/grouping, leaks nothing) and is
  carried regardless of `caps.css`, like `cont_id`.
- **Fail closed / bounded.** Every value arrives already clamped by `css`
  (`CSS_LEN_MAX`, `CSS_BORDER_W_MAX`, enum ranges). `block_id` is `-1` when the run
  is not inside a box-carrying block. Geometry uses `box_tree`'s existing
  `BT_MAX_DEPTH`/`BT_MAX_CHILDREN` caps.

## Step A — fields threaded onto `pv_run` and `rd_block`

All are ints (the wire is int32, like every existing run field). Defaults are the
no-op sentinels so a page with no author box styling renders identically.

| Group | Fields | Unset sentinel |
| :-- | :-- | :-- |
| grouping | `block_id` | `-1` |
| box-sizing | `box_sizing` | `0` (unset → content-box) |
| padding (px) | `pad_t`, `pad_r`, `pad_b`, `pad_l` | `0` |
| border width (px) | `bord_tw`, `bord_rw`, `bord_bw`, `bord_lw` | `PV_LEN_UNSET` |
| border style | `bord_ts`, `bord_rs`, `bord_bs`, `bord_ls` | `0` (none) |
| border color | `bord_tc`, `bord_rc`, `bord_bc`, `bord_lc` | `-1` |
| border-radius (px) | `border_radius` | `PV_LEN_UNSET` |
| box-shadow | `bsh_dx`, `bsh_dy`, `bsh_blur`, `bsh_spread`, `bsh_color`, `bsh_inset` | `0/0/0/0/-1/-1` |
| outline | `outline_w`, `outline_style`, `outline_color` | `PV_LEN_UNSET / 0 / -1` |

### Given-When-Then

- **Given** a block element with `border:2px solid #f00; padding:10px; box-sizing:border-box`
  and author CSS enabled (`caps.css`), **when** the page is rendered, **then** every
  run inside that block carries the same `block_id`, `bord_*w = 2`, `bord_*s = solid`,
  `bord_*c = 0xff0000`, `pad_* = 10`, `box_sizing = border-box`.
- **Given** the same page with author CSS **disabled**, **when** rendered, **then**
  `rd_block` carries the box-decoration fields at their unset defaults (gated off),
  but `block_id` is still set (structure).
- **Given** a page with no author box styling, **when** rendered, **then** every run
  has `block_id = -1` and all box-decoration fields at unset → byte-identical output.
- **Given** runs of two sibling bordered blocks, **when** rendered, **then** the two
  blocks get distinct `block_id`s (document order), and runs of each share theirs.

### How they are produced (page_view)

`resolve_context` already finds the nearest block-level ancestor (`*block`) and,
with the `got_hbox` logic, the nearest block ancestor that declares a horizontal
box. Mirroring that: the nearest block ancestor whose resolved `css_style` declares
any box decoration (`css_has_boxdeco`) is the **box-carrying block**; its
`css_style` fills the box-decoration fields and its element gets a `block_id` from a
document-order registry (`container_id`, reused). A run with no box-carrying block
ancestor gets `block_id = -1` and unset decoration.

### IPC (tab.c)

`write_view`/`read_view` serialize the new ints **in the same order on both sides**
(the desync gotcha — `[[freedom-render-pipeline-ipc]]`), inserted as one contiguous
block right after the existing `box_*` fields, reconstructed via a new
`pv_set_boxdeco`/`pv_set_box_border` setter pair on the just-appended run.

### render_doc

`rd_build` copies `block_id` **and** the box-decoration fields **only with `caps.css`**.
Unlike `cont_id` (flex/grid is page structure, always applied), `block_id` exists
*only* to group runs for painting the author box decoration, which is presentation;
with author styling off there is no box to draw, so the runs are not grouped and the
layout is byte-identical to before. (The event dispatcher's node identity, Stage 4,
is a separate always-available field.)

## Step B — geometry (`bt_node` + `bt_layout`)

`gui/browser_ui.c` `layout_doc` groups consecutive `rd_block`s sharing a `block_id`
into a block box, builds a `bt_node` (`[[box_tree]]`) carrying the block's
margins/padding/border as `bx_edges`, sets the leaf `content_h` from the measured
text height, calls `bt_layout(root, content_w)` for the border-box rect, and places
the existing `rc_row`s inside the box's content rect (origin shifted by
border+padding). Blocks with `block_id = -1` keep today's flat vertical flow
(default byte-identical). `box-sizing` selects whether the author `width` is the
content box or the border box.

## Step C — paint

A new `paint_box_decoration(cr, rect, b)` draws, in order: box-shadow (offset rect,
blurred via a soft stroke, spread, color; `inset` clips inward), the background fill
within the border, the 4 borders (per-side width/style/color; `solid`/`dashed`/
`dotted`/`double`; uniform `border-radius` via `cairo_arc` corners), and the
outline (outside the border box). Reuses the Cairo surface the painter already owns.

## Step D (DELIVERED) — nested box composition: a box-definition TREE

> **Why D.** Steps B/C grouped a *maximal run of consecutive `rd_block`s sharing a
> `block_id`* into one box. That is a flat 1:1 model: a parent box whose runs are
> interrupted by a child box is **split into two boxes** (the child renders as a
> sibling, not nested). Modern pages are 1:N (a wrapper with many children) and N
> levels deep (`<section><div class="card"><div class="card-body">…`), so this fails
> visually — confirmed: an `.outer{border;bg;padding}` wrapping
> `<p>…</p><div class="inner">…</div><p>…</p>` paints two outer boxes with the inner
> as a sibling. Step D makes boxes a **tree**: every box knows its `parent_id`, and a
> child box composes *inside* its parent's content rect.
>
> Two structural problems Step B/C could not solve and D does:
> 1. **Identity is a tree, not a flat id.** A run's box must know its ancestor boxes
>    so the painter can open them outer→inner and keep the parent open across the
>    child. → `parent_id`.
> 2. **A text-less wrapper carries no run.** `<div class="card"><div class="body">
>    <p>…` has the card's decoration on *no* run (only `.body`'s runs exist, and they
>    carry `.body`'s decoration). Duplicating one box's decoration on each of its runs
>    (Step A) cannot represent a box that owns no direct text. → decoration moves off
>    runs onto a **box-definition list** that has an entry for *every* box, text-less
>    wrappers included.

### Data model — `pv_box_def` / `rd_box_def` (the box tree)

The box decoration is **moved off `pv_run`/`rd_block`** (extinguishing the per-run
duplication of Step A) into a parallel, document-order list of box definitions:

| Field | Meaning |
| :-- | :-- |
| `parent_id` | block_id of the nearest box-carrying block *ancestor*, or `-1` (root box) |
| the 27 decoration fields | `box_sizing`, `pad_*`, `bord_*{w,s,c}`, `border_radius`, `bsh_*`, `outline_*` — same set, same sentinels as Step A |

`pv_view` gains `pv_box_def *boxes; size_t nbox` (bounded by `PV_MAX_CONTAINERS`,
the same cap as `block_id`s). `rd_doc` gains `rd_box_def *boxes; size_t nbox`. A box's
`block_id` **is its index** in this list. `pv_run`/`rd_block` keep only `block_id`
(which box a run belongs to). So a run "knows its parent" via
`boxes[run.block_id].parent_id` — the tree lives in one place, not copied per run.

### How produced (page_view)

`resolve_context` walks a run's ancestors child→parent. The first box-carrying block
(`css_has_boxdeco`) is the run's `block_id` (registered in `block_reg`, decoration
recorded into `boxes[id]`). Walking on, **each** further box-carrying ancestor is
also registered/recorded, and the parent link is stamped: the previously seen (more
inner) box's `parent_id` is set to the current (outer) box's id. Idempotent — every
run that passes through the same ancestors records the same defs and links. Result:
`boxes[]` has an entry for every box-carrying block (text-bearing or not), each with
its decoration and `parent_id`; the outermost box has `parent_id = -1`.

### IPC (tab.c)

After the run array, `write_view`/`read_view` serialize `[nbox]` then each box def's
fields **in the same order on both sides** (the desync gotcha,
`[[freedom-render-pipeline-ipc]]`), via a `pv_add_box_def` builder on the receiving
view. `block_id` stays on each run (unchanged).

### render_doc

`rd_build` copies the box-def list into `rd_doc.boxes` **only with `caps.css`** (the
whole list is author presentation; with author styling off the list is empty and the
runs are not grouped → byte-identical to before, exactly as Step A gated `block_id`).
`block_id` on `rd_block` stays gated by `caps.css` for the same reason.

### Painter (gui/browser_ui.c `layout_doc`) — open-box STACK reconciliation

Replaces the single `cur_box_id` with a bounded stack (`RC_BOX_STACK_MAX`, 16) of
open boxes. For each run it computes the run's box **path** root→`block_id` from the
box-def `parent_id` chain (bounded), then reconciles: pop (close, innermost first)
any open box not on the path; push (open, outermost first) any path box not yet open,
using its `rd_box_def` decoration. A child box is placed inside its parent's **content
rect** (`bx_place` against the parent's inner width/left), so it nests instead of
splitting the parent. Boxes are recorded and painted in **open (tree/document) order**
— the parent's decoration paints before the child's, i.e. the implicit z-order of the
tree is respected (Gap "Z-Index y Composición", implicit case — see below). At
top level (empty stack) the geometry is the Step B/C single-level placement → **single
boxes and the default path stay byte-identical**.

### Given-When-Then (Step D)

- **Given** `.outer{border;bg;padding}` containing `<p>a</p><div class="inner">
  {border}<p>b</p></div><p>c</p>` with `caps.css`, **when** rendered, **then** one
  outer box encloses all three paragraphs and the inner box nests inside it (not three
  boxes); `boxes[inner].parent_id == outer`, `boxes[outer].parent_id == -1`.
- **Given** a text-less wrapper `.card{border}` whose only child is `.body{padding}`
  with text, **when** rendered, **then** `boxes[]` has an entry for *both* `.card` and
  `.body` (the card's border paints although the card owns no run), and
  `boxes[body].parent_id == card`.
- **Given** author CSS **disabled**, **when** rendered, **then** `rd_doc.boxes` is
  empty and every `block_id == -1` → byte-identical to the no-box render.
- **Given** a page with no author box styling, **when** rendered, **then** `boxes`
  is empty → byte-identical.

### v1 limitations (Step D)

Carried from Step B/C plus: a box's own list-indent is not applied to the box rect
(boxes are assumed block-level, indent 0); a flex/grid container still ends all open
boxes (a box broken by a flex container is not composed); nesting depth capped at
`RC_BOX_STACK_MAX`; `box-sizing` border-box width math still not subtracted.

## Stage 2 — `position` (relative / absolute / fixed) + `z-index` stacking

> **Why now.** Modern sites use `position:absolute` for **navigation structure**
> (sticky-look headers, dropdowns, cookie banners, modals, fixed navbars). The CSS
> cascade already resolves every value (`css_style.position` / `inset_*` / `z_index`,
> `include/css.h:223-225`) and `pv_box_def` already carries it
> (`include/page_view.h:193-195`); the dom_debug dump already shows it
> (`src/dom_debug.c:118-185`). The gap is purely a render-pipeline one: the values
> never leave `pv_box_def`, so a `<div style="position:fixed;top:0;z-index:100">`
> paints at the same static rect as `<div>`. Stage 2 closes the gap: a box out of
> flow is removed from the in-flow layout, placed against its containing block, and
> painted in the correct stacking order.

### Position values (mirror of `css_position`; 0 = static/unset)

| Constant | Value | Meaning |
| :-- | :-- | :-- |
| `BT_POS_STATIC` | 0 | In-flow; no offset. The default (also for unset). |
| `BT_POS_RELATIVE` | 2 | In-flow; offset by insets. Siblings unaffected. |
| `BT_POS_ABSOLUTE` | 3 | Out-of-flow; placed against nearest positioned ancestor. |
| `BT_POS_FIXED` | 4 | Out-of-flow; placed against the viewport. |
| `BT_POS_STICKY` | 5 | Fail-closed → treated as RELATIVE (no scroll hooks in v1). |

The `1` gap is intentional: `css_position` reserves `CSS_POS_STATIC = 1` for the
explicit in-flow keyword; both 0 and 1 are "static" for layout purposes (the
pv_box_def comment already says "0 unset/static"). This keeps the wire format a
direct copy of `css_position` and avoids an extra translation layer.

### Inset sentinels

`pv_box_def.inset_{top,right,bottom,left}` use the CSS sentinels:

| Sentinel | Meaning | Stage 2 handling |
| :-- | :-- | :-- |
| `CSS_LEN_UNSET` (0) | Not declared | Default: at the containing block's edge (left=cb.x, top=cb.y) |
| `CSS_LEN_AUTO` (-2147483647) | `auto` | Treated as unset in v1 (no shrink-to-fit solver) |
| signed px | Pixels | Used as-is |

Only `top` and `left` insets are honored in v1. `right`/`bottom` are read but
ignored (a v1 limitation; documented below) — a positioned box without `top` is
anchored at the containing block's top edge, which is the common case.

### Data model — one new pure struct + one new function

No changes to `bt_node` (the layout tree stays in-flow only). A new struct carries
the out-of-flow result:

```c
/* One positioned box in the final paint order. The GUI paints
 * rc_layout.rows (in-flow) first, then these in the returned order. */
typedef struct bt_positioned {
    size_t  box_index;   /* index into pv_box_def (== block_id) */
    int     z_index;     /* signed, or 0 if unset; CSS_LEN_UNSET -> 0 */
    size_t  doc_order;   /* depth-first pre-order index, for stable tiebreak */
    double  x, y, w, h;  /* final content-box rect, viewport-relative */
} bt_positioned;
```

A new pure function resolves all positioning in one pass:

```c
bt_status bt_resolve_positioning(
    const pv_box_def   *boxes,        /* box tree (parent_id chain) */
    size_t              nbox,
    const double       *box_x,        /* in-flow geometry, indexed by box_index, or NULL */
    const double       *box_y,
    const double       *box_w,
    const double       *box_h,
    double              viewport_w,   /* initial containing block (= content area) */
    double              viewport_h,
    bt_positioned      *out,          /* caller-owned; sorted by (z_index, doc_order) */
    size_t              out_cap,
    size_t             *out_count     /* number of positioned boxes found */
);
```

Semantics:

1. **Walk the box tree** (via `parent_id` chain) depth-first, assigning `doc_order`
   in pre-order. Idempotent — each box gets one `doc_order` regardless of how many
   runs reference it.
2. **For each box with `position != BT_POS_STATIC` (i.e. relative/absolute/fixed/
   sticky):**
   - **`RELATIVE` / `STICKY` (treated as relative):** keep the in-flow geometry
     (`box_x[i]`, `box_y[i]`, `box_w[i]`, `box_h[i]`) and offset by
     `(inset_left, inset_top)`. If an inset is `CSS_LEN_UNSET`/`CSS_LEN_AUTO`, the
     offset on that axis is 0.
   - **`ABSOLUTE`:** walk the `parent_id` chain to find the nearest ancestor with
     `position != BT_POS_STATIC`. If found, the containing block is the ancestor's
     `(box_x[a], box_y[a], box_w[a], box_h[a])`. If not, fall back to the viewport
     `(0, 0, viewport_w, viewport_h)`. The box's `(x, y)` = containing-block origin
     + `(inset_left, inset_top)`; `(w, h)` come from the in-flow geometry (the box
     does not collapse — its measured content height stands).
   - **`FIXED`:** containing block = the viewport. Same offset rules.
3. **Sort `out[]` by `(z_index ASC, doc_order ASC)`.** Negative z-index boxes sort
   first (they paint behind in-flow content); the caller's painter uses this order
   to split paint into two passes (see GUI below).
4. `out_count` is the number of positioned boxes found (may exceed `out_cap`; the
   caller can detect truncation by comparing `out_count` to a prior measure pass,
   or by re-calling with a larger cap).

### Status codes

| Code | When |
| :-- | :-- |
| `BT_OK` | Success. `out_count` set; `out[]` filled up to `out_cap` (truncation reported). |
| `BT_ERR_NULL_ARG` | `boxes` is NULL and `nbox > 0`, or `out_count` is NULL. `box_x/y/w/h` may be NULL for boxes without an in-flow rect — `bt_resolve_positioning` then treats those boxes as zero-size at `(0, 0)`. |
| `BT_ERR_RANGE` | `nbox` > `BT_MAX_POSITIONED` (caller-side cap; the function fails closed rather than overflowing). |

### Security posture (carries from Step D)

- **No network, no execution.** Pure geometry on already-resolved, already-fuzzed
  `pv_box_def` values. The values arrive already clamped by `css`
  (`CSS_LEN_MAX`, `CSS_ZINDEX_MAX = 1<<20`, enum ranges), so the solver never
  trusts an author value.
- **Author presentation, gated.** `position`/`z-index` reshape content (a fixed
  navbar covers the viewport; a modal covers the page). Stage 2's wire values are
  author presentation → `render_doc` copies them ONLY with `caps.css`, like the
  box decoration subset. The default render path (caps off) stays byte-identical
  to Step D — no `position` field ever appears on a run or box, and the
  positioning pass is a no-op.
- **Containment.** A positioned box cannot escape the layout: `position:fixed`
  is bounded by the viewport; `position:absolute` is bounded by the nearest
  positioned ancestor (the box tree has bounded depth `BT_MAX_DEPTH`); the
  containing block is always derived from the caller's geometry, never from
  user-controlled input. `z_index` is clamped to `CSS_ZINDEX_MAX` upstream.
- **Fail closed.** Out-of-cap / out-of-range / NULL inputs return an error
  status; the caller skips the positioning pass for that frame rather than
  painting garbage.

### GUI integration (`gui/browser_ui.c`)

The `rc_layout` struct gains a positioned section (sized by `BT_MAX_POSITIONED`):

```c
bt_positioned positioned[BT_MAX_POSITIONED];
size_t        npositioned;
```

**`layout_doc` (in-flow pass, as today, plus one addition):**

1. Walk `rd_doc` blocks in document order.
2. For a block with `block_id >= 0` and `pv_box_def[block_id].position ==
   BT_POS_RELATIVE` (or STICKY), offset the open box's `(x, y)` by `(inset_left,
   inset_top)` in `open_box`/`reconcile_boxes`. Sibling rows are unaffected
   (the box's own content moves).
3. For a block with `position == BT_POS_ABSOLUTE` or `BT_POS_FIXED`:
   **skip the in-flow placement entirely** (no row, no box, no margin; the
   `prev_bottom`/`pending_gap` are not touched). Record the block for the
   out-of-flow pass.
4. For everything else, today's flat flow (Step D) is unchanged.

**`position_doc` (new, runs after `layout_doc`):**

1. Build a parallel `pv_box_def`-indexed geometry array from the in-flow pass
   (each block's final `(x, y, w, h)` if it was placed; zero otherwise).
2. Call `bt_resolve_positioning(boxes, nbox, gx, gy, gw, gh, content_w, content_h,
   L->positioned, BT_MAX_POSITIONED, &L->npositioned)`.
3. On `BT_OK`, `L->positioned` is sorted by stacking order.

**`paint_content_row` / `paint_doc` (the painter):**

1. Paint in-flow boxes (`paint_box_decoration` + `paint_content_row` per `rc_row`,
   in document order) — byte-identical to today.
2. Walk `L->positioned` from index 0 to `npositioned`. For each:
   - If `z_index < 0`: paint now (behind in-flow; but since in-flow already
     painted, this is a v1 limitation — see below). **v1:** skip negative z-index
     boxes (they would have to paint before in-flow, requiring a two-pass
     painter that doesn't exist yet).
   - If `z_index >= 0` or unset: paint the box decoration + its block's runs at
     the resolved `(x, y, w, h)`. A positioned box is a mini `rc_layout`: one
     text run painted at the box's content origin, decoration drawn around it.
3. For the **headless** export paths (`ui_render_pdf`, `ui_render_png`): the
   same `layout_doc` + `position_doc` + paint sequence runs; the only
   difference is the surface.

### IPC + page_view plumbing

The values are **already** in `pv_box_def` (`include/page_view.h:193-195`); they
were resolved by `css` (Hito 23b-7) and carried by `page_view` into the box
tree. The IPC `tab.c` `write_view`/`read_view` serialises `pv_box_def` in full
**today** (the Step D wire format includes the whole struct). So:

- **No new `pv_box_def` fields.** The `position`/`inset_*`/`z_index` fields are
  already there; the writer/reader already round-trip them.
- **No new `rd_block` / `rd_box_def` fields.** `render_doc` already copies the
  box-def list to `rd_doc.boxes` (`src/render_doc.c`); the new fields ride
  along. The whole list is gated by `caps.css` — unchanged.
- **`dom_debug` already prints them** (`src/dom_debug.c:118-185`: `pos=...`,
  `inset(t/r/b/l)`, `z=N`). After Stage 2 the values finally **affect pixels**.

This is the cheap property of the closed Hito 23b-7 + Step D: the wire was
already complete, so Stage 2 only adds the **consumer** (the pure solver + the
GUI's stacking pass). No desync risk on `tab.c` (nothing new on the wire).

### Given-When-Then

- **Given** a `position:relative` box with `top:10px;left:20px`, **when** laid
  out, **then** the box's content rect is offset by `(20, 10)` from its
  in-flow position; siblings are unaffected; `dom_debug` reports
  `pos=relative inset(t=10 l=20)`.
- **Given** a `position:absolute` box with `top:0;left:0` inside a
  `position:relative` wrapper, **when** laid out, **then** the absolute box
  sits at the wrapper's `(0, 0)`; outside any positioned ancestor, it sits at
  the viewport's `(0, 0)`.
- **Given** a `position:fixed` box with `top:0;right:0`, **when** laid out,
  **then** the box is anchored to the viewport's top-right (v1: only `top` is
  honored, so the box sits at the viewport's top; `right` is read but ignored).
- **Given** three positioned boxes with `z-index:1`, `z-index:10`, `z-index:-1`
  in document order, **when** the stacking pass runs, **then** the sorted order
  is `[z=-1, z=1, z=10]`; the painter paints the `z=-1` skip in v1, then
  `z=1` and `z=10` in that order on top of the in-flow content.
- **Given** `position:sticky`, **when** laid out, **then** it is treated as
  `position:relative` (fail-closed) and the same offset rules apply; `dom_debug`
  still reports `pos=sticky` for honesty.
- **Given** author CSS **disabled** (`caps.css` off), **when** rendered, **then**
  the `rd_doc.boxes` list is empty, the in-flow layout runs unchanged, and
  `npositioned == 0` → byte-identical to the no-position render.
- **Given** a `position:absolute` box whose ancestor chain has no positioned
  node, **when** laid out, **then** the containing block falls back to the
  viewport; the box is bounded by `content_w` × `content_h`.
- **Given** a `nbox > BT_MAX_POSITIONED` page, **when** resolved, **then** the
  function returns `BT_ERR_RANGE`; the GUI skips the positioning pass for that
  frame and the in-flow layout is still painted (fail-closed: no garbage).

### v1 limitations (Stage 2)

Carried from the previous steps plus the new positioning scope:

- **`right`/`bottom` insets read but ignored.** Only `top` and `left` are
  honored. A box without `top` anchors at the containing block's top; without
  `left`, at its left. Adding `right`/`bottom` is a future extension (no
  algorithm blocker; just the containing-block math).
- **`CSS_LEN_AUTO` for insets treated as `CSS_LEN_UNSET`.** No shrink-to-fit
  solver (the box uses its measured content size).
- **`position:sticky` → `relative`.** No scroll hooks in the render; the user
  can still see the value in `dom_debug`. Real sticky needs an event from the
  scroll path that the render currently doesn't have.
- **Negative `z-index` skipped.** They would need to paint **before** in-flow,
  requiring a two-pass painter. The `z_index` value is read and sorted; the
  GUI skips `z_index < 0` entries for now and logs nothing (silent fail-closed;
  a hostile doc can't use this to hide content because the default is to NOT
  skip — only negative-z is the missing case).
- **Containing block = border-box, not padding-box.** CSS says absolute's
  containing block is the padding box of the nearest positioned ancestor; v1
  uses the border-box (the difference is the border width, usually small).
  Not a security issue; a precision issue documented here.
- **No percentage or viewport units** for insets (`top: 50%` is ignored and
  treated as `top: 0`). The cascade already drops `%`/vw for box-model lengths
  (Hito 23b-3); the same fail-closed carries.
- **Positioned image / input blocks** (rare but possible) paint their text
  placeholder at the resolved rect; the image decode path is unchanged.

### Out of scope (Stage 2)

- `position:sticky` with scroll (own follow-up: needs the scroll path).
- `right`/`bottom` insets and shrink-to-fit (`CSS_LEN_AUTO` math).
- Negative `z-index` paint (two-pass painter).
- Padding-box vs border-box containing block (precision).
- Flex/grid per-item sizing (Stage 3 of the plan).
- Event dispatcher / click → JS (Stage 4 of the plan).
- Layout invalidation / incremental repaint (gated by JS-mutation path;
  CLAUDE.md §7.3 Hito 20e p2 follow-up).

## Gaps deferred with reason (Layout Invalidation only)

The remaining gap after Stage 2 is layout invalidation. Its status is recorded
here so the gap is *closed as a decision*, not left ambiguous:

- **Layout invalidation ("dirty flag").** A per-block dirty flag so a JS style
  mutation re-lays-out only the changed box, instead of rebuilding the whole tree per
  frame. **Blocked:** Freedom has **no incremental render path** — a JS DOM/style
  mutation re-derives the *entire* `tab_page` view in the worker, ships it over IPC,
  and the GUI rebuilds the whole `rd_doc` and repaints (`render_current`). A `dirty`
  field would have no consumer until that path exists. It belongs to the existing
  roadmap item "**repintado incremental en mutación**" (CLAUDE.md §7.3, Hito 20e p2
  follow-up): the dirty tracking, the incremental relayout, and the JS-mutation hook
  land together, or the flag is dead. Not added until then.

## Errors

No new status codes. `page_view`/`render_doc`/`tab` keep their existing tables;
malformed author CSS was already dropped fail-closed by `css` before reaching here.

## Notes

- `block_id` is the seed the **event dispatcher** (Hito 20e p2) will also use, but
  the dispatcher needs the run's *own element* `node_id` (a `dom_node_id`), which is
  threaded separately when that hito starts — not here.
- Default-init duplication across the three `pv_append*` helpers is collapsed into a
  shared `run_init_style_defaults` (boy-scout) so the ~28 new fields are defaulted in
  one place, not three.
