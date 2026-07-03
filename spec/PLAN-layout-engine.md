# Plan — Layout Engine (box engine) + Event Dispatcher (click → JS)

> **Status:** Stage 0 keystone (node identity) **CERRADO**; Stage 4 dispatcher
> **PARCIALMENTE CERRADO** (click handler fires over IPC and GUI wires it). Stage 1-3
> (box engine) pendientes. Encodes the owner's priority for the next bucket: turn
> Lexbor + CSS resolved values into a real box tree `(x,y,w,h)` that Cairo paints.
>
> Maps to the existing roadmap (CLAUDE.md §7.3): **Hito 23b-8 (motor de cajas)**
> and **Hito 20e parte 2 (eventos interactivos)**. **No new dependencies.** Every
> stage follows the §3 cycle: spec → test (red) → code (green) → refactor →
> `make asan` → fuzz (where hostile input is touched) → docs.

---

## Why now

Two structural GAPs dominate "the modern web looks right":

1. **Box engine.** Hito 23b-7 already *resolved* ~40 layout/decoration fields into
   `struct css_style` (`include/css.h:223-252`): `position`/insets/`z-index`,
   `box-sizing`, `border-*`/`border-radius`, `box-shadow`, `outline`, flex-per-item
   (`flex-grow/shrink/basis/order`, `align-*`), and grid-per-item
   (`grid-template-rows`, `row-gap`, `grid-auto-flow`, `span N`). **Nothing consumes
   them.** They never leave `css_style`: `page_view`'s `resolve_context` never
   extracts them, they are not in `pv_run`/`rd_block`, never threaded over IPC,
   never painted. Result: zero new pixels since 23b-7.

2. **Event dispatcher.** A click resolves to a link href (`link_at_point`,
   `gui/browser_ui.c:2730`) or an `rd_block*` (`input_at_point`, `:2795`) — but
   neither carries a **DOM node identity**, so the GUI cannot tell the worker
   "node N was clicked, fire its handler." `js_dom` only queues `load`/
   `DOMContentLoaded` handlers (`src/js_dom.c:361`), drained once by
   `__fireDeferred` (cap 64); `click`/`input` are silently ignored.

Both are blocked by the **same missing keystone**: a stable element id threaded
`dom → page_view (pv_run) → IPC → rd_block`. Build it once; both features use it.

The existing assets to reuse (do **not** rewrite):
- `box_tree` / `bt_layout` (`include/box_tree.h:70`) — recursive block/flex/grid
  geometry, already producing border-box rects. **Currently orphaned.**
- `bx_place` (`src/box_style.c`) — horizontal box placement (Hito 23b-3), already
  wired in `layout_doc`.
- The `cont_id` pattern (`pv_run`/`rd_block`) — groups runs of one flex/grid
  container in document order. The keystone mirrors this exactly.
- The JS navigation gate (Hito 20e p1): worker records raw intent
  (`__navReq`), parent reads via `jd_take_nav_request` (`src/tab.c:378`) and gates
  via `ln_resolve` (`:932`). The click dispatcher mirrors this trust model.
- The kept-alive worker (`browser_window.tab_worker`, `drop_repl_worker`,
  `freebug_repl_worker`) used by the Freebug REPL — the dispatcher reuses it so a
  click evaluates against the live DOM without a fresh fork.

---

## Stage 0 — Keystone: stable node identity `dom → pv_run → rd_block` ✅ CERRADO

**Goal:** every `pv_run` carries the `dom_node_id` (document-order element id,
`include/dom.h:34`) of its source element. It survives IPC into `rd_block`. **No behavior
change** (additive field, sentinel `DOM_NODE_NONE`); default render byte-identical.

- `pv_run` gains `dom_node_id node_id;`.
- `page_view` assigns it via a pre-order walk (`pv_node_map`) that matches the walk
  used by `dom_build`, validated with a red test against `dom_index`.
- IPC: add `node_id` to `write_view`/`read_view` (`src/tab.c`) **in the same order on
  both sides** (the known desync gotcha) via `pv_set_node_id`.
- `rd_block` gains `dom_node_id node_id`; `rd_build` copies it **always**
  (identity is structure, not author styling).
- `make clean` after the struct grows (header-dep gotcha).

**Tests:** `test_page_view` (+2: setter model; node_id matches `dom_index`),
`test_render_doc` (+1: carried by default), `test_tab` (+1: round-trip IPC).
**Validation:** `make test`, `make asan`, `make fuzz-pv` verde.

---

## Stage 1 — Box engine: thread + paint border/box-sizing/padding/shadow/outline

The user's #1 priority: cajas `(x,y,w,h)` que Cairo pinta.

**1a — value plumbing (no pixels yet).** Extract the 23b-7 box-decoration fields
from `css_style` in `resolve_context` into new `pv_run` fields (border 4-side
width/style/color, border-radius, box-sizing, box-shadow layer, outline, plus
`padding-top/bottom` now that boxes are grouped). Thread through IPC and into
`rd_block`, **gated by `caps.css`** (a border/box can reshape content → author-
presentation family, like the box model and colors; identity/structure stays
always-on). Mirror the line-height/text-decoration plumbing template exactly
(`[[freedom-line-height]]`).

**1b — per-block box grouping → `bt_node` tree.** In `gui/browser_ui.c` `layout_doc`,
group consecutive `rd_block`s by `block_id` into block boxes, build a `bt_node`
tree (display/margins/padding/gap/flex/grid from the grouped block + measured text
content height as the leaf `content_h`), call `bt_layout(root, content_w)` to get
border-box rects, and position the existing `rc_row`s inside each box's content
rect. This replaces the ad-hoc vertical flow for boxed blocks; non-boxed blocks
keep today's flow (default byte-identical). Reuse `bx_place` for the horizontal cap.

**1c — paint.** In `paint_content_row`/a new `paint_box_decoration`: draw the 4
borders (width/style/color; `solid`/`dashed`/`dotted`/`double`), `border-radius`
(single uniform radius via `cairo_arc`), `box-shadow` (single layer: offset +
blur approximated, spread, color, inset), `outline`, and honor `box-sizing`
(content-box vs border-box width math) and vertical padding. Visual review via
`--author-css --download-pdf` → `mutool` → Read (`/visual-review`).

**Out of scope for Stage 1 (own follow-ups):** `position`, flex/grid per-item
sizing, `%`/viewport units, nested-box composition, corner-by-corner radius,
multi-layer shadow.

**Tests:** `test_box_tree` (+ grouping cases), `test_css` already covers value
resolution; `test_page_view` (+ box fields extracted). **Fuzz:** `fuzz-pv`,
`fuzz-css` (already exercise the hostile path).

---

## Stage 2 — Box engine: `position` (relative / absolute / fixed / z-index)

On the `bt_node` tree from Stage 1: `position:relative` offsets a box by its
insets without affecting siblings; `absolute`/`fixed` take the box out of flow and
place it against the nearest positioned ancestor / viewport; `z-index` orders the
paint of positioned boxes (a stacking pass after the in-flow paint). `sticky` =
basic (clamp within container during scroll) or deferred. Visual review.

**Out of scope:** full stacking contexts, `sticky` edge cases, `overflow`
clipping/scroll containers.

---

## Stage 3 — Box engine: flex/grid per-item

Honor the per-item fields resolved in 23b-7 inside `bt_layout`'s flex/grid path:
`flex-grow/shrink/basis/order`, `align-items/self/content`, `justify-items`,
`flex-direction`/`flex-wrap`, `grid-template-rows`, `row-gap`, `grid-auto-flow`,
`grid-column/row: span N`. `box_tree` already has `grow/shrink/basis` slots on
`bt_node` (`include/box_tree.h:46`) — wire the resolved values in and extend
`flex_layout` for wrap/align where missing. Visual review.

---

## Stage 4 — Event dispatcher: click → JS handler (Hito 20e p2, *simple*) ✅ PARCIAL

Reuses Stage 0's `node_id`. Mirrors the JS-navigation trust model (worker records
intent, **parent gates**, GUI applies).

- **Hit-test → node.** `node_at_point` (nuevo en `gui/browser_ui.c`) camina
  `rc_layout` y devuelve el `node_id` del fragmento bajo el cursor. `rc_frag` gana
  el campo `node_id`, propagado desde `rd_block` en todos los sitios que construyen
  frags (layout normal, cajas posicionadas, PDF, PNG).
- **Worker stores per-node handlers.** `js_dom` ahora soporta
  `addEventListener('click', fn)` y `element.onclick = fn`; los handlers se guardan
  en un registro JS interno (`__clickRegistry`) indexado por handle, así no hay
  JSValue retenido en C.
- **IPC `OP_CLICK`.** Nuevo op `[OP_CLICK][node_id: int32]` al worker vivo. El
  worker llama `jd_fire_click`, que construye un evento mínimo con
  `target`/`preventDefault`, ejecuta el handler y **re-deriva** la vista. La
  respuesta comparte el formato de `OP_LOAD` con `navreq_len == 0`.
- **GUI re-renders.** `dispatch_click` en `gui/browser_ui.c` envía el click al
  worker, reemplaza `w->doc` con la vista actualizada (`apply_click_result`) y, si
  el punto era un enlace, sigue el enlace tras la mutación (la navegación por JS
  sigue fluyendo por `jd_take_nav_request` → `ln_resolve` con `JS_NAV_MAX`).
- **Secure by Default:** el dispatcher solo corre cuando `caps.js` está activo para
  el host (Hito 20). Con JS off, los clicks se comportan como antes.

**Limitaciones v1 (pendientes):** no hay bubbling a ancestros, no hay coords en el
evento, no hay `input`/`change`/`keydown`, timers async reales, repintado
incremental, capture-phase ni `stopPropagation`.

**Tests:** `test_js_dom` (+4: addEventListener, onclick, preventDefault, sin
handler), `test_tab` (+1: OP_CLICK E2E muta DOM y devuelve vista actualizada).
**Fuzz:** `fuzz-js` verde.

---

## Doctrine notes (carry into the specs/memory when each stage closes)

- Identity (`node_id`/`block_id`) is **structure**, carried regardless of
  `caps.css` (like `cont_id`); box **decoration** (border/shadow/outline) is
  **author presentation**, gated by `caps.css` (like colors / box model).
- The click dispatcher keeps the Zero-Trust split: worker fires handlers and
  records intent; the **parent** gates navigation (`ln_resolve`) and the GUI
  re-applies full network policy. A compromised worker can mutate its own inert
  view but cannot navigate off-policy.
- No `io_uring` in the worker (unchanged). No new dependency. `-fvisibility=hidden`
  stays. `make clean` after any `pv_run`/`rd_block`/`css_style` struct grows.

---

## Sequence & verification

```
Stage 0 keystone (node_id/block_id)        ~0.5 day  — unblocks both
Stage 1 box: thread + paint border/...     ~2-3 days — first visible win
Stage 2 box: position/z-index              ~1-2 days
Stage 3 box: flex/grid per-item            ~2 days
Stage 4 event dispatcher (click→JS)        ~2 days
```

Each stage: `make test` + `make asan` exit 0; `fuzz-pv`/`fuzz-css`/`fuzz-js` clean
where the hostile path changed; `/visual-review` (`--author-css --download-pdf`)
for anything that paints, with the interactive Wayland window staying pending the
owner (consistent with every GUI hito). `docs/index.html` + `README.md` updated
only after green tests + clean ASan + green fuzz.
