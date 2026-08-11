# Spec: `parity` — Firefox render parity measurement harness

> Status: DONE — measurement harness operational. See [[freedom-parity-harness]].

## 1. Purpose

Structural divergence measurement of Freedom's PNG output against Firefox 140 ESR
headless. The metric is not pixel-parity (rasterizer and fonts differ), but
structural: does the page have the same content in the same order at the same
approximate positions.

`make parity` renders a corpus of 5 real-page HTML snapshots with both engines
at `--window-size=1000,<freedom_height>`, then runs `pngdiff` to compute three
orthogonal signals composited into a single score.

## 2. Corpus

`tests/parity/pages/` — real-page snapshots plus purpose-built probes, all
self-contained (stylesheets inlined):

| Page | Source | What it exercises |
| :-- | :-- | :-- |
| `slashdot.html` | slashdot.org | Float columns, nested flex/grid in floats, multi-band layout |
| `hackernews.html` | news.ycombinator.com | Simple table-based grid, tight typography |
| `ddg-results.html` | duckduckgo.com | Overflow clipping, flex results, word-wrap |
| `wikipedia.html` | en.wikipedia.org | Long-form article, images, infobox float |
| `jkanime.html` | jkanime.tv | Bootstrap grid, CSS heavy, flex nesting |
| `rem-62.html` | probe | `html{font-size:62.5%}` rebasing `rem` |
| `float-beside.html` | probe | Text flowing BESIDE a float, `float:right` box side |
| `table-fit.html` | probe | Table columns sized by content |
| `ua-metrics.html` | probe | User-agent margins per tag + `line-height: normal` |

**Los probes son deliberadamente más altos que 768 px.** Firefox headless reporta la
altura del *viewport* en páginas cortas, y ahí `h_ratio` —el término dominante del
score— no mide nada.

Un probe aísla **una** divergencia y la vuelve un número. `ua-metrics.html` es el
ejemplo canónico: secciones separadas para divs sin margen, `<p>` **con** margen (la
guarda contra sobre-corregir), listas, filas de tabla, `blockquote` y cajas de línea a
varios tamaños. Entró en 18.94 y quedó en 0.98.

Each page is saved with its stylesheets inlined — the harness never touches the
network (deterministic, Zero Trust).

## 3. pngdiff metrics

`tools/pngdiff.c` (257 lines, pure C, libpng only) computes three signals:

| Metric | What it measures | Why |
| :-- | :-- | :-- |
| `h_ratio` | Freedom height / Firefox height | Single highest-signal scalar: a 4x ratio means collapsed layout |
| `col_mae` | Mean absolute error of column-ink profiles (200-bucket projection) | Detects column collapses, width mis-distribution, giant icons |
| `row_mae` | Mean absolute error of cumulative vertical ink distributions | Detects extra/missing bands, reordered content |

Algorithm: two-pass libpng stream (O(width) memory, never holds a full bitmap).
Pass 1 finds background luminance (modal pixel). Pass 2 accumulates ink profiles
against that background (ink threshold: 24.0 luminance delta).

Composite score: `h_ratio + 10 × col_mae + 10 × row_mae`.

Exit 0 on success, 1 on read/decode failure.

Run directly: `./build/pngdiff freedom.png firefox.png` prints a TSV line:
`h_fd h_ff h_ratio col_mae row_mae score`.

## 4. Make targets

### `make parity`

For each page in the corpus:
1. `./build/freedom --author-css --images --download-png=<out>` — Freedom PNG
2. Extracts `Saved PNG (N px)` height from Freedom output
3. `firefox --headless -profile <tmp> --screenshot <out> --window-size=1000,N` — Firefox PNG (same canvas height)
4. `./build/pngdiff` — compare, emit per-page row
5. Print table sorted by divergence, total composite score
6. Diff against `tests/parity/baseline.tsv` if present

### `make parity-update`

Depends on `parity`. Copies `build/parity/current.tsv` → `tests/parity/baseline.tsv`.

### `make layout-diff`

For each of 20 `examples/*.html`:
1. `./build/freedom --dump-layout --author-css` → `build/layout/<name>.txt`
2. `diff -u` against frozen `tests/parity/layout/<name>.txt`
3. Any diff ⇒ FAIL.

`ui_dump_layout` prints total_h, row geometry (top/h/x_off/bg_w), box rects (bid/x/top/w/h),
positioned boxes, and container table. Deterministic, textual, headless, no Wayland.

### `make layout-update`

Re-freezes `tests/parity/layout/*.txt` from current `examples/*.html`.

## 5. Current baseline (2026-08-08)

| Page | Score |
| :-- | --: |
| ddg-results | 33.62 |
| hackernews | 20.25 |
| jkanime | 54.21 |
| slashdot | 27.64 |
| wikipedia | 47.45 |
| **Total** | **183.17** |

## 6. Verification flow per sub-step (four gates)

1. `make layout-diff` — diff zero on 20 `examples/*.html`
2. `make test` + `make clean && make asan` — clean
3. `make parity` — divergence does not increase for any page
4. `/visual-review` — `--download-png` + Read of a representative page

## 7. Limitations & contract

- Score is relative, not absolute. A lower score means less structural divergence;
  zero is impossible (different rasterizers / font stacks). The measure is useful
  for ranking and for detecting regressions, not for declaring "done."
- Firefox headless requires `-profile` with a writable directory. The harness
  creates a clean temp profile per run in `build/parity/ffprof/`.
- The corpus is static HTML — it tests layout, not fetch/JS/network behaviour.
- `col_mae` and `row_mae` are sensitive to background colour differences (white
  in Freedom vs off-white in Firefox). The modal-luminance background detection
  in pngdiff compensates for this.
