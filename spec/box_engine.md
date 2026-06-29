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
> Out of scope for this hito (own follow-ups): `position`/`z-index` (explicit
> stacking; implicit tree z-order IS respected by Step D), flex/grid per-item sizing,
> `%`/viewport units, corner-by-corner radius, multi-layer shadow, layout invalidation
> ("dirty flag"). Those `css_style` fields stay resolved-but-unconsumed.

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

## Gaps deferred with reason (Layout Invalidation, explicit Z-Index)

The owner flagged two further gaps alongside nesting. Neither is implemented, because
implementing them **now** would be ceremonial dead code (the project's anti-dead-code
doctrine, cf. SOP/CORS-by-construction). Their status is recorded here so the gap is
*closed as a decision*, not left ambiguous:

- **Layout invalidation ("dirty flag").** A per-block dirty flag so a JS style
  mutation re-lays-out only the changed box, instead of rebuilding the whole tree per
  frame. **Blocked:** Freedom has **no incremental render path** — a JS DOM/style
  mutation re-derives the *entire* `tab_page` view in the worker, ships it over IPC,
  and the GUI rebuilds the whole `rd_doc` and repaints (`render_current`). A `dirty`
  field would have no consumer until that path exists. It belongs to the existing
  roadmap item "**repintado incremental en mutación**" (CLAUDE.md §7.3, Hito 20e p2
  follow-up): the dirty tracking, the incremental relayout, and the JS-mutation hook
  land together, or the flag is dead. Not added until then.

- **Explicit `z-index` / stacking of positioned boxes.** **Implicit** z-order (paint
  in tree/document order) is now **correctly respected** for nested boxes by Step D
  (parent paints before child; siblings in document order). **Explicit** `z-index`
  only changes paint order when boxes **overlap**, and boxes overlap only once
  `position:absolute`/`fixed`/`relative` take them out of normal flow — which is
  Stage 2 (`position`), not yet built. `z-index` is already *resolved* in `css_style`
  (Hito 23b-7) but threading/sorting it before `position` exists would reorder boxes
  that never overlap → no visible effect = dead code. Deferred to the `position` hito
  (PLAN-layout-engine.md Stage 2), which adds out-of-flow placement and the stacking
  pass together.

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
