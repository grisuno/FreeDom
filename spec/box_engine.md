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
> Out of scope for this hito (own follow-ups): `position`/`z-index`, flex/grid
> per-item sizing, `%`/viewport units, nested-box composition, corner-by-corner
> radius, multi-layer shadow. Those `css_style` fields stay resolved-but-unconsumed.

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
