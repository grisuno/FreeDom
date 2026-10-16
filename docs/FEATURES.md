# Freedom — Features & Rendering Engine

[Back to README](../README.md)

## Features

- Portable C11 — no C++, no Rust, no hidden dependencies
- Strong process-based sandboxing for each tab: the worker is **forked and re-exec'd**
  so it inherits none of the browser's memory (a compromised tab cannot read other
  tabs' content; fresh ASLR), then confined with seccomp-bpf with **W^X** (no
  executable memory — `PROT_EXEC` `mmap`/`mprotect` are killed), Landlock, per-tab
  namespaces, and an undumpable worker so secrets cannot leak via core dump or
  ptrace. The syscall allowlist is **deny-by-default**, so **`io_uring` is blocked**
  in the worker — it is a seccomp-bypass primitive, so it never gets in.
- JavaScript sandbox using QuickJS-ng
- Hardened build with stack protection, PIE, RELRO, and FORTIFY_SOURCE
- Wayland + Cairo GUI backend with Client-Side Decorations (CSD)
- HarfBuzz text shaping (ligatures, GPOS kerning, complex scripts) on the trusted
  side, with local fonts only — never in the sandboxed worker, never a web font fetch
- Lexbor HTML parser and renderer
- Strict request policy using Public Suffix List + blocklist/allowlist
- Post-quantum hybrid cryptography support (X25519MLKEM768)
- Headless mode for automation and testing, including `--dump-video` to download and pipe video streams
- Anti-fingerprinting techniques
- Comprehensive test suite, fuzzing, and integration tests

### Vertical rhythm, heading scale and named grid areas (14 August 2026)

Three engine-wide corrections, each isolated in a probe **measured against Firefox
headless before any code changed**. Structural divergence over the parity corpus fell
from **154.06 to 126.04**.

- **Vertical margins now collapse (CSS 2.1 §8.3.1).** The gap between two block boxes
  used to be `max(previous bottom margin, a theme constant)`, and only once a line of
  *text* had been painted. A page whose content is boxes — a separator, a spacer, an
  icon tile, an empty card — never paints one, so **no block on it received any margin
  at all**: three 20px divs with `margin-bottom:30px` stacked at 0/20/40 where Firefox
  puts 0/50/100. The rule lives in a new pure module, `block_flow` (`bf_`), and is the
  normative one — `max(0, positives) + min(0, negatives)`, which stops agreeing with
  `max(a, b)` the moment a margin is negative, and `margin-top:-1px` to overlap borders
  is everyday markup. Parent/child collapsing works in both directions: a first child's
  top margin moves the *parent*, while a last child's bottom margin stays *inside* a
  box that has bottom padding.
- **Headings keep their size under an author base font-size.** `body{font-size:16px}`
  — or its `font:` shorthand, which is on essentially every real page — used to render
  `h1`, `h2` and `p` at exactly the same size, flattening the document's hierarchy. An
  absolute font-size replaces the user-agent heading scale only when the author
  declared it *on the heading*; on an ancestor it is the heading's inherited value and
  `h1{font-size:2em}` still doubles it.
- **`grid-template-areas` places items by name.** Grid items were placed round-robin at
  `index % columns`, so every named layout — how essentially every modern portal is
  built — came out with its regions in source order. Named areas resolve to rectangles
  (`spec/grid_areas.md`) and explicit placement runs before auto-placement, per CSS Grid
  §8.3/§8.5. The `grid-template` / `grid` shorthands parse too.

Also fixed on the way: `::before` content is inline content and no longer takes a row of
its own (it was doubling the height of Wikipedia's reference list); multi-column
fragmentation no longer reads row positions its own earlier pass had already rewritten;
and a flex/grid item with both `height` and `padding` is no longer exactly its vertical
padding too short.

### Nested flex/grid + inline-block flow (31 July 2026)

The two structural render breaks are closed, both **measured** against Firefox headless:

- **Nested flex/grid containers.** A `header{display:flex}` holding a flex
  `<nav><ul>` — the navbar of nearly every modern site — used to split into two
  stacked rows with the inner items' boxes drawn at the wrong size. A run carries only
  its *innermost* container, and laying out the outer one needs the outer container's
  parameters, which in a grid-of-flex-cards **no run carries at all**. So containers
  now have a descriptor table (`pv_cont_def`, indexed by `cont_id`) holding
  `parent_id`/`parent_item` plus the container parameters; it crosses the IPC as its
  own array. `resolve_context` describes the whole ancestor chain instead of stopping
  at the innermost, the layout loop groups by the **root** container, and
  `layout_container` **recurses** into items that are themselves containers, sizing
  them by the nested container's max-content width.
- **`display:inline-block` flows inside its line.** A badge, pill or chip in the
  middle of a sentence used to break it into three: text, badge alone on a full-width
  row, rest of the text. Registering a box was the problem — opening a box is a block
  operation that flushes the line. An inline-level box is now tracked *off* the box
  stack and materialised when the line flushes, from the extent of its own fragments.
  An inline-block that *opens* a line keeps the old block treatment (shrink-wrapped and
  placed by `text-align`), which is what a standalone centred call-to-action needs.

Both are locked by pixel regression tests. See `spec/page_view.md`.

**Still open, and now the loudest remaining gap:** table auto width (shrink-to-fit)
plus `colspan`/`rowspan` — every table still spans the full page and ignores spans.

### Typography & inline flow parity (31 July 2026)

Four defects that made ordinary pages look broken, all **measured** against Firefox
headless on the same HTML (`firefox --headless --screenshot` versus
`freedom --download-png`):

- **Absolute font sizes are absolute.** `px`, `pt`, `rem`, viewport units and the size
  keywords resolve against the 16px root and **replace** the user-agent heading scale;
  `em`/`%` stay relative and chain outward until an absolute size anchors them
  (`.card{font-size:14px} .card h3{font-size:1.2em}` → 16.8px). Before this the percent
  was multiplied onto the UA size, so every author-styled `<h1>` painted at **double**
  its declared size. See `spec/css.md`, "font-size: absolute vs relative".
- **The user-agent metrics match a real browser.** A 16px base — the same root the CSS
  engine resolves `px`/`rem` against, so the two cannot drift — the CSS 2.1 heading scale
  (2.0 / 1.5 / 1.17 / 1.0 / 0.83 / 0.67), `line-height` 1.2, and headings that **inherit**
  their colour instead of taking a theme accent. A heading's bold now rides the resolved
  font weight, so `h1{font-weight:normal}` finally works. See `spec/box_style.md` §4b.
- **Whitespace is collapsed, never invented.** `<strong>bold</strong>,` renders as `bold,`
  and no longer as `bold ,`. The word flow inserted a space before every word that did not
  open a line, which put a stray gap before every comma, bracket and full stop following an
  inline element — on every page with emphasis, links or `<code>`.
- **Out-of-flow elements are block boxes** (CSS 2.2 §9.7), so an absolutely positioned
  `<span>` registers a box and honours `right`/`bottom` instead of landing in the flow at
  full width. As a side effect the PNG export is now sized by the lowest box rather than by
  the text flow alone: a page made only of boxes used to export as a 0px image.

All four are locked by pixel regression tests in `tests/test_freedom.c`.

(Nested flex and inline-block flow, listed as open when this section was written, are
closed above.)

### Inline SVG + Firefox render parity (30 July 2026)

Inline `<svg>` renders: shapes (`rect`/`circle`/`ellipse`/`line`/`polyline`/`polygon`),
full `<path>` data (including elliptical arcs), `<g>` groups with inherited paint and
composed `transform`, `fill="currentColor"` icons that take the surrounding text colour,
`viewBox` scaling, and `<text>`.

It renders **unconditionally** — unlike `<img>`, which stays behind the images toggle —
because the grammar the parser accepts has **no URL form at all**: `<image>`, `<use>`,
`<foreignObject>`, `<script>` and `<style>` are dropped together with their subtrees, so
an inline SVG structurally cannot fetch. The parser (`svg_render`, `sv_`) is pure, bounded
and fuzzed (`make fuzz-svg`); the Cairo half (`svg_paint`, `svp_`) only draws already
validated geometry. See `spec/svg_render.md`.

The same push closed five render gaps **measured** against Firefox
(`firefox --headless --screenshot` versus `freedom --download-png` on the same file):

- A row's background band now stops at the first ancestor **box** that paints a background
  of its own. Every gradient hero used to lose its headline under an opaque band of the
  page colour, painted on top of the gradient the box had just drawn.
- A flex/grid container knows its own box, so `justify-content: space-between` paints one
  band across the header instead of one rectangle per item with the page showing through.
- `display: inline-block` shrink-wraps to its content and is placed by the parent's
  `text-align` — a centred call-to-action button was a full-page-width bar.
- A box **nested inside** a flex/grid item paints (badge pills, icon chips, avatars).
- Replaced elements (`<img>`, `<svg>`) are placed by `text-align` and honour their
  **declared** `width`/`height`, and a `max-width; margin: 0 auto` block keeps its width
  cap inside a decorated ancestor.

### Modern Web Rendering (18 July 2026)

A modernization push across eight phases delivered a rendering engine comparable
to modern browsers for trusted hosts (hosts present in both `allow.conf` and
`js.conf`):

**Animations & Transitions (R1):** pure interpolation engine (`interp` module)
supporting CSS easing functions (linear, ease, ease-in/out, steps, cubic-bezier),
scalar and color value interpolation, keyframe interpolation, and a full animation
state machine handling delays, direction, fill modes, and iteration counts.
`animation-duration` CSS property parsed and flows through the full pipeline
(CSS -> page_view -> IPC -> paint). `@keyframes` at-rules are parsed and stored;
`animation-name`, `animation-iteration-count`, `animation-direction`,
`animation-fill-mode`, `animation-timing-function`, and `animation-delay` are
all parsed through the CSS cascade. In the GUI, boxes with animations
automatically form stacking contexts and composite with animated opacity blended
from the interpolation engine against wall-clock time.

**Advanced Selectors (R2):** `:first-of-type`, `:last-of-type`, `:only-of-type`,
`:nth-of-type(An+B)`, `:nth-last-of-type(An+B)`, `:empty`, `:target`, and
`:lang(ident)` pseudo-classes fully parsed and matched. The existing `:not()`,
`:is()`, and `:where()` functional pseudo-classes were already implemented.
The DOM element chain (`css_chain.c`) was extended with per-type sibling counting
and child count for accurate matching. `:empty` correctly detects elements with
zero child nodes. `:lang()` performs case-insensitive prefix matching on the
`lang` attribute. Pseudo-elements are correctly distinguished: `::before` and
`::after` match in the CSS cascade (for style resolution) but never match in
DOM queries like `querySelector` (matching real browser behavior).

**CSS Filters (R3):** `filter: blur(Npx)` and `filter: grayscale(N%)` parsed
through the full pipeline. In the GUI, boxes with filters form stacking contexts.
The grayscale filter is applied via Cairo pixel manipulation: the box's offscreen
group is extracted as an image surface, each pixel is converted to grayscale
(weighted luminance: 0.299R + 0.587G + 0.114B), and the modified surface is
blended back with partial grayscale factor. Anti-DoS bounded at 4096px.

**Layout & Positioning (R4):** `position: sticky` implemented — boxes pin to the
viewport top when scrolled past their in-flow position, common for fixed
navigation bars. `right` and `bottom` CSS insets now honored for absolute/fixed
positioned boxes: when `right` is set and `left` is auto, the box anchors to
the right edge of its containing block (and similarly for `bottom`). These were
already parsed but previously ignored in the box-tree position resolver.

**Firefox-parity pass on modern layout (2026-07-27):** the render was diffed
against Firefox 140 ESR headless on the same HTML, and the gaps that broke modern
pages were closed rather than guessed at.

- **Flex actually flexes.** A flex item without `flex-basis` is sized to its
  *measured content* instead of an equal share of the row, so `justify-content`
  (`space-between`/`center`/`space-around`) finally has leftover space to
  distribute and a three-link nav bar shrink-wraps instead of spanning the page.
  Item `margin` counts as main-axis space. Every flex container goes through the
  flex engine (previously only those whose items declared a flex property).
- **Containers paint their own box.** A `display:flex`/`display:grid` container
  now paints its background/border/radius and lays its items out inside its
  padding; nesting is preserved, so a flex row inside a
  `max-width; margin: 0 auto` wrapper stays inside the wrapper.
- **`display:inline-block` flows horizontally.** A parent whose element children
  are all inline-block lays out as an anonymous flex row — nav bars, badge
  strips and button groups no longer stack one per line.
- **Out-of-flow boxes shrink-wrap.** `position:absolute` with `width:auto` sizes
  to its content (a `right`-anchored badge lands at the right edge instead of
  off-screen), and a `position:relative` wrapper holding *only* positioned
  children generates its own box, so it paints, reserves its height and acts as
  their containing block.
- **Table cells generate boxes**, so `td { border: 1px solid }` paints (`<th>`
  centered by UA default); **inline backgrounds** (`<code>`, `<mark>`) paint
  behind their own glyphs instead of smearing across the line; `text-align`
  inside a grid/flex cell centers within that cell; and `<li>` no longer
  inherits a paragraph's `1em` margin, so lists are tight like a browser's.

Still v1: text does not wrap *beside* a lone float, `align-items` centers
against the tallest item rather than an explicitly taller container, and
`width:auto` is not stretched between `left`+`right`.

**Out-of-flow subtree + line-box pass (2026-07-30, Stage 2d):** measured against
Firefox on a live Wikipedia article; four chained pipeline bugs closed.

- **The whole `position:absolute`/`fixed` subtree leaves the flow.** Blocks
  living in *child* boxes of an absolute box (a dropdown menu's `<li>` items)
  used to lay out in flow, reserving huge blank bands before the article; a
  flex/grid container inside an absolute subtree slipped past the check
  entirely. Pure `bt_oof_anchor`/`bt_oof_root` classify each block's box chain
  (cycle-bounded, fail-open); the positioned pass measures and paints the whole
  subtree stacked. Wikipedia's header shed ~2700px of reserved blanks.
- **The IPC codec now carries `clip: rect()` and the explicit-height flag.**
  Both were resolved by the worker but never serialized, so the trusted side got
  a valid-looking 0×0 clip rect and clipped every positioned box to nothing.
- **Form controls keep their own box across the pipe.** The run reader dropped
  `block_id`/`node_id` for input runs, so a checkbox-hack control
  (`position:absolute; opacity:0`) painted as a visible ghost checkbox instead
  of entering the positioned pipeline.
- **A line box is as tall as its tallest fragment (CSS 2.1 §10.8).** The last
  run's `line-height` used to win: Wikipedia's `.mw-editsection{line-height:0}`
  after every heading collapsed the heading's line and the next paragraph
  painted through the glyphs. The line now takes the max leading over its
  fragments.

**Background Enhancements (R5):** `background-position` parsed with keyword
(`left`/`center`/`right`/`top`/`bottom`) and pixel value support. Applied as
a Cairo translate offset in the box decoration painter, with `center`
auto-resolving to `(box_w - img_w) / 2`. Multi-layer `background-image` with
comma-separated URLs (`url(a.png), url(b.png)`) — second layer painted behind
the first with independent sizing, repeat, and position. `radial-gradient()`
parsed and painted via `cairo_pattern_create_radial` with center at box center.
Gradient stop positions (e.g. `red 20%, blue 80%`) now consumed instead of
always-even spacing.

**Nested Compositor Tree (R6):** stacking-context boxes now recursively compose
their entire subtree as a single offscreen Cairo group. A parent with opacity
properly blends its children (including nested stacking contexts) as one unit —
fixing the previous limitation where child boxes with their own opacity were
composited independently on top of the parent's group. Implemented via a
recursive `paint_nested_children` helper that traverses the box tree.

**JavaScript Modernization (R7):** `<script defer>` attribute parsed in the HTML
parser and honored via two-pass script execution: sync/external scripts run first,
deferred scripts run after, all sharing the same per-page JS time budget.
`customElements.define()` now stores constructors in a live registry and fires
`connectedCallback` during `__fireDeferred`. Binary `arrayBuffer` response type
in XHR/fetch: `__hostFetch` returns raw binary as an ArrayBuffer, and
`responseType='arraybuffer'` in XHR as well as `fetch().arrayBuffer()` return
real binary data. DOM events `keydown`, `input`, `change`, `blur`, and `focus`
were already fully wired (discovered during the audit).

**Pseudo-elements (R8):** `::before` and `::after` parsed in the selector engine
and matched in the CSS cascade (rules like `div::before { color: red; }` apply
their styles). The `content` property is parsed (quoted strings) and stored in
`css_style`. DOM queries correctly reject pseudo-elements (matching browser
behavior). Full content injection into the display list during the page_view
walk is deferred to a follow-up.

### Additional Modern Features

- **Trusted-host full experience (Hito 28):** a host trusted **twice** (in
  `allow.conf` **and** `js.conf`) automatically gets author CSS, images, and
  full JS — no per-session toggles needed.
- **Parallel subresource prefetch (Hito 29):** a preload scanner on the trusted
  side scans raw HTML for `<link rel=stylesheet>` and `<script src>`, downloading
  them in parallel (up to 4 threads) through the same policy-gated fetcher while
  the worker parses. Total wait tends to the maximum latency instead of the sum.
- **Advanced Layout Engine:** full box model per HTML tag (margins, padding,
  display, border), flexbox with `gap`/`justify-content`/`flex-wrap` multi-line/
  `align-items`/`align-self`, CSS Grid with sized tracks (`fr` weights, fixed px,
  `repeat()`/`minmax()`, `grid-column: span N`), and recursive box-tree layout
  with margin collapsing.
- **GUI:** visible scrollbar, Vim-style shortcuts (`j`/`k`, `gg`/`G`, etc.),
  window controls (maximize, minimize, resize, titlebar drag), sepia/light/dark
  themes, hover link preview, loading indicator, multi-tab with shortcuts.
- **Anti-fingerprinting:** normalized `User-Agent` and `Accept-Language` shared
  by all Freedom users — a common Firefox/Linux identity.
- **Omnibox:** type a URL to navigate (`https://` added, `http://` upgraded) or
  anything else for a DuckDuckGo HTML (no-JS) search. Dangerous schemes like
  `javascript:` are searched, never executed.
- **Per-domain JS policy + live JS:** Secure by Default — page JS off unless opted
  in. Global tri-state mode (off/allowlist/on) plus `js.conf` allowlist. Inline
  scripts execute in the sandboxed worker against a memory-safe writable DOM.
- **Tor & I2P:** `.onion` routing via SOCKS5h proxy, `.i2p` via HTTP proxy, both
  fail-closed (never leak to clearnet).
- **Encrypted persistent profile (Hito 10):** preferences, bookmarks, and history
  sealed with AES-256-GCM under a per-device Argon2id key, atomic 0600, nothing
  readable on disk.
- **External stylesheets and scripts:** fetched by the trusted parent under full
  network policy for trusted hosts — the sandboxed worker never touches a socket.
- **Real async JS timers:** `setTimeout`/`setInterval` with actual delays on a
  virtual clock the trusted parent drives (the worker cannot wake itself).
- **PDF/PNG export:** `Ctrl+P` for vector PDF, `Ctrl+Shift+P` for full-height PNG.
- **Safe downloads:** `Ctrl+S` with fail-closed filenames, atomic 0600 writes.
- **Page zoom:** `Ctrl++`/`Ctrl+-`/`Ctrl+0` with 50-300% ladder.
- **Box model:** `margin`/`padding`/`width`/`max-width` with `box-sizing:
  border-box`, `border-radius`, `box-shadow` (outset and inset), `outline`,
  `visibility:hidden`, `cursor:pointer`, `text-overflow:ellipsis`, `word-break`,
  `overflow:hidden` clipping.
- **Math functions:** `min()`/`max()`/`clamp()` in lengths, `calc()` with
  dimensional checking, `var()`/custom properties with depth-capped lookups.
- **Logical properties:** `margin-inline`, `padding-block`, `inset-inline`,
  `inline-size`/`block-size` with physical LTR mapping.
- **Automatic dark mode:** `@media (prefers-color-scheme: dark)` applies
  automatically when the dark theme is on.
- **CSS transforms:** `translate()`, `scale()`, `rotate()`, `skew()`/`skewX()`/
  `skewY()`, and `matrix()` (QR-decomposed at parse time) via real Cairo affine
  matrix, pivoted at `transform-origin` (keywords + percents; default center).
  Single function per declaration; `matrix()` covers the composed case.
- **Viewport units:** `vw`/`vh`/`vmin`/`vmax` resolve against the normalized
  1920x1080 desktop (the same fixed identity `@media` width queries and the
  anti-fingerprint screen report), inside `calc()`/`min()`/`max()`/`clamp()`
  and `font-size` too. `min-height:100vh` heroes and `calc(100vh - 80px)`
  layouts now work with zero real-window leakage.
- **Glassmorphism:** `backdrop-filter: blur(Npx)` (+ `-webkit-` alias) samples
  and blurs the already-painted backdrop under the box before its translucent
  background composites on top; `rgba()`/`hsla()` background alpha is honored
  in the box fill (`background: rgba(255,255,255,0.25)` panels).
- **JS media queries + reveal-on-scroll:** `matchMedia()` really evaluates
  width/height/orientation queries against the same normalized 1920x1080
  identity (identity signals pinned: light scheme, fine pointer, hover);
  `IntersectionObserver` delivers one synthetic `isIntersecting:true` entry per
  `observe()` in the deferred phase — AOS-style scroll-reveal content that
  used to stay stuck at `opacity:0` now renders. All values are synthetic
  constants: zero real geometry, scroll order, or timing leaks.
- **Form controls:** native GET/POST without JS, text inputs, checkboxes,
  select menus, submit buttons.
- **Image formats:** PNG, JPEG, WebP, and static GIF (own bounded pure-C LZW
  decoder, no giflib). Inline `data:` images. All decoded inside the sandboxed
  worker.
- **Video playback paced by PTS (v2, July 19):** frames display at their
  presentation timestamps against the wall clock (pure `md_pacer` brain; the
  consumer regulates the whole pipeline through pipe backpressure — no sleeps).
  The decoder process sends microsecond PTS with per-segment time bases, the
  first HLS segment's frames are no longer lost to the probe, codecs drain only
  at end-of-stream (v1 drained per segment, killing every later segment), and
  audio writes to `aplay` are non-blocking best-effort (the UI thread can never
  freeze on a full audio pipe). Verified end-to-end: 3 HLS segments in, 150/150
  frames out, monotonic PTS, clean EOS.
- **Repaint decoupled from the media pipeline (v2.1):** repainting per received
  frame let a slow full-window software repaint drag the whole pipeline (audio
  included) below real time. Video now repaints at most once per 3x its own
  measured paint cost (33 ms floor): light pages play at full rate, heavy pages
  degrade to a slideshow while the timeline and the audio stay real-time
  (skipped frames drop by overwrite, like any player). The `aplay` pipe carries
  a ~1 MiB cushion so catch-up bursts are re-timed, not dropped.
- **Modern `<video>`/`<audio>` element surface:** multiple `<source>` children
  are selected by `type` (HLS/MPEG-TS/MP4 preferred), fallback content inside
  media elements is suppressed (the element renders instead), and page JS gets
  an identity-safe `HTMLMediaElement` facade — `play()`/`pause()`/
  `canPlayType()`, attribute-reflected `muted`/`loop`/`controls`, `buffered`
  TimeRanges, `new Audio(src)` — so player scripts run without throwing and
  without touching the network.

## Current Status (July 31, 2026)

- Advanced HTML rendering with box model, flex/grid, margin collapsing
- Browser-accurate typography: 16px root shared by the theme and the CSS engine,
  CSS 2.1 heading scale, absolute `px`/`pt`/`rem` sizes that replace (not multiply)
  the user-agent size, and headings that inherit their colour
- CSS whitespace collapsing at inline-run boundaries (no invented space before
  punctuation that follows `<strong>`/`<em>`/`<a>`/`<code>`)
- Inline `<svg>`: shapes, `<path>` (arcs included), `<g>` transforms, `currentColor`,
  `viewBox` scaling, `<text>` — always rendered, structurally unable to fetch
- Clickable links + image support (PNG + JPEG + WebP + static GIF)
- Inline `data:` images with zero network request
- CSS `background-image` with `linear-gradient()`, `radial-gradient()`,
  `conic-gradient()` (128-sector fan, `from <deg>`, stop positions in `%`/`deg`,
  two-position stops = hard edges for pies/stripes), and
  `url(...)` (fetched/decoded under same policy as `<img>`)
- Gradient text: `background-clip: text` / `-webkit-background-clip: text` +
  `-webkit-text-fill-color: transparent` fills glyphs with the element gradient
- `filter: drop-shadow(dx dy blur color)` — shadow of the group's real alpha
  silhouette (rounded cards, PNG transparency), not the box rect
- `background-position`, `background-size`, `background-repeat`, multi-layer
- `border-radius` on backgrounds, borders, shadows, and outlines
- `box-sizing: border-box` honored
- CSS `filter: blur()` and `filter: grayscale()` parsed, grayscale painted
- Animation engine with `animation-duration` and `@keyframes` parsing
- Advanced selectors: `:nth-of-type()`, `:first-of-type`, `:empty`, `:lang()`,
  `:not()`/`:is()`/`:where()`
- `::before`/`::after` parsed and matched in CSS cascade
- `position: sticky` (pins to viewport on scroll)
- `right`/`bottom` insets honored for absolute/fixed positioning, including on
  inline tags (`position:absolute` makes an element a block box, CSS 2.2 §9.7)
- Gradient stop positions consumed (not always evenly spaced)
- Nested compositor tree (opacity of parent blends entire subtree)
- `<script defer>` two-pass execution
- `customElements.define()` with `connectedCallback`
- Binary `arrayBuffer` in XHR/fetch
- Real async JS timers on a virtual clock
- `innerHTML` getter and setter
- Anti-fingerprinting network identity (normalized User-Agent + Accept-Language)
- Omnibox address bar (navigate or DuckDuckGo HTML search)
- Native forms (GET/POST, no JS)
- Save page as vector PDF (`Ctrl+P`) or PNG (`Ctrl+Shift+P`)
- Safe downloads (`Ctrl+S`, fail-closed filenames, 0600)
- Page zoom (`Ctrl++`/`Ctrl+-`/`Ctrl+0`) and reload (`Ctrl+R`/`F5`)
- Encrypted persistent profile (preferences, bookmarks, history)
- Author CSS with cascade (descendant/child/sibling combinators, attribute
  selectors, pseudo-classes, `!important`) — never phones home
- External stylesheets fetched by trusted parent under full policy
- Box model (`margin`/`padding`/`width`/`max-width`), text presentation
  (`font-family`, `text-transform`, `letter-spacing`, etc.)
- `visibility`, `cursor`, `text-overflow`, `word-break`, `overflow:hidden`
- Math functions, logical properties, `var()`/custom properties
- Automatic dark mode (`@media (prefers-color-scheme: dark)`)
- CSS transforms: `translate()`, `scale()`, `rotate()` via Cairo affine matrix
- Headless mode, `--dump-console`, `--dump-dom`, `--dump-layout` , `--dump-video`
- Strong per-tab sandboxing (seccomp-bpf W^X, Landlock, namespaces)
- Docker + noVNC
- Tor & I2P routing (`.onion`/`.i2p` + torify)
- Distraction-free (reader) mode (`Ctrl+D`)
- Debian packaging
- CI/CD + fuzzing + MCP automation

