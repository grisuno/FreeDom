# tests/wpt — WPT static reftest subset (benchmark axis #2)

Vendored from [web-platform-tests/wpt](https://github.com/web-platform-tests/wpt)
(BSD-3-Clause; each file keeps its upstream license header — do not strip it).

## What lives here

A curated subset of WPT CSS reftests (`css-overflow`, `css-sizing`,
`css-flexbox`, `css-grid`, `css-multicol`, `css-tables`, `css-break`,
`css-align`), filtered for this engine's doctrine:

- **static or script-inert**: the harness renders with JS disabled on BOTH sides
  (Freedom renders JS-off by default; Firefox runs with `javascript.enabled=false`
  + a dead proxy, exactly like `make parity`), so page scripts never execute and
  both engines measure the same document;
- **self-contained**: no remote URLs, no Ahem/custom fonts (this engine drops
  `@font-face` fail-closed, so font-dependent tests would measure policy, and
  `make parity` already taught that lesson with wikipedia's navboxes);
- **test + reference vendored together**: the `-ref.html` files are fixtures for
  provenance, not measured — `make wpt` renders each TEST in both engines and
  compares them with `tools/pngdiff`, the same way `make parity` does.

## Relationship with `make parity`

- `make parity` measures REAL pages (the objective function for render work).
- `make wpt` measures SPEC corners (the conformance backlog: what the engine
  does not implement yet, per CSS area).

A WPT test that scores ~0 guards implemented behavior against regressions; a
test that scores high is a measured TODO, not a failure — `expected.tsv`
freezes both, and `make wpt` fails only on NEW divergence (a score that rose
more than 1.0 above expectation, or a test with no expectation at all).

## Updating

- `make wpt` — score every test against Firefox, report PASS (score <= 5.0),
  TOTAL, and deltas vs `expected.tsv`. Firefox screenshots at
  `--window-size=1000,H_FD` so both bitmaps share one canvas (most WPT tests
  are sub-viewport, where a height ratio measures the window, not the
  document); the score is pure profile divergence and `H_FD` vs `FF_REAL`
  ride along as info columns.
- `make wpt-update` — freeze current scores as `expected.tsv`.
- Adding tests: copy test + ref from upstream WPT, keep headers intact, keep
  them static-or-inert and self-contained (see filter above), then
  `make wpt-update`. Prefer small files (< 15 KB). Shared fixtures go in
  `tests/wpt/<area>/support/` and `tests/wpt/support/` (same relative layout
  as upstream, so `support/` and `../support/` resolve in both engines).
- Refreshing from upstream: re-clone WPT sparsely
  (`git clone --depth 1 --filter=blob:none --sparse`, cone patterns
  `css/css-overflow` etc.), re-apply the filter, copy. Never point the
  harness at a live checkout: the corpus must be frozen and offline.

## Triage backlog (first run 2026-09-06: 64/100 PASS)

Worst offenders first — each is a future hito, ordered by score:

- `flexbox/auto-height-column-with-border-and-padding` (23.33) — flex column,
  auto height + border/padding.
- `sizing/border-box-and-max-content-00[12]` (22/21) — max-content intrinsic
  width measurement (no intrinsic measure yet).
- `overflow/abspos-shrink-to-fit-with-scrollable-descendant` (17.27),
  `flexbox/aspect-ratio-intrinsic-size-01[23]` (16-17),
  `overflow/button-with-scrollable-descendant` (10.70),
  `sizing/abspos-stretch-*` (10-12) — abspos shrink-to-fit / intrinsic sizes
  inside scroll containers and flex items.
- `sizing/box-sizing-content-box-001/002`, `box-sizing-border-box-003`
  (11-14) — box-sizing + replaced/percent widths.
- `sizing/block-fit-content-as-initial` (12.66) — `max-height:100%` against an
  indefinite containing-block height must compute to `none` (CSS 2.1 §10.7);
  the engine resolves the percentage instead and squeezes a 60px image to 34.
- `flexbox/align-self-015` (11.58) — column flex + wrap + auto margins.
- `multicol/abspos-containing-block-outside-spanner` — Freedom lays out
  30000 px (canvas cap): robustness bug, multicol + abspos blowup.
- Validated green by this axis on day one: `clipped-scroller-add-content`,
  `float/inline-block-with-scrollable-descendant`, `incremental-scroll*`
  (0.00), `document-element-overflow-hidden-scroll` (0.24) — the scroll-clip
  hito (spec/page_view.md 2026-09-06) measured on spec grounds.
