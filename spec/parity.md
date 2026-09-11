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

### Viewport truth (2026-09-07): the headless canvas IS the viewport

Both engines render "a 1000px window", but Freedom's headless PNG laid out at
`1000 - 2×24` (image padding) while Firefox headless lays out at the full 1000
(no scrollbar gutter, no window margins in screenshot mode — measured: a 974
container for 26px of body padding). The 48px systematic gap propagated
ABSOLUTELY down every inset chain (slashdot story text 50px too narrow at every
level), exactly the class of harness-lies-about-the-document taught by the
wikipedia-JS lesson (§7.4): never debug the engine against a reference that
renders a different document — or a different WIDTH. `PNG_MARGIN` is now 0:
headless lays out edge to edge at viewport 1000, 1:1 with the reference canvas
(the interactive window keeps its own margins + scrollbar gutter). This already
matches `@media`'s viewport (`ui_render_viewport_w` = 1000), so the change also
removes an internal inconsistency. Re-freezing `layout/` (20 pages, structure
verified identical modulo reflow), `baseline.tsv`, and `wpt/expected.tsv` (28
WPT deltas verified float-free) is part of the change, not an afterthought.

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

## `make geom` — la geometría de los dos motores, lado a lado (2026-08-14)

`make parity` dice **cuánto** difiere una página; no dice **qué** caja se movió.
`make geom PAGE=archivo.html [SEL=selector]` responde eso:

```
make geom PAGE=tests/parity/pages/margin-collapse.html
make geom PAGE=probe.html SEL="section,div,p"
```

Imprime el `--dump-layout` de Freedom y deja en `build/geom/firefox.png` la geometría
que Firefox resuelve para la MISMA página — como texto, no como render: la página se
**copia** (nunca se modifica en el sitio) con un script que reemplaza el `<body>` por el
`getBoundingClientRect()` de cada elemento que matchea `SEL` (por defecto, todo elemento
con clase). Así una diferencia de layout se lee como dos columnas de números en vez de
adivinarse comparando dos capturas.

Es el bucle que cada tanda de paridad corre de verdad: **aislar el caso en una página
chica, medir LOS DOS motores, y recién entonces tocar código.** Las trampas de Firefox
headless documentadas en `parity` valen igual acá (ruta absoluta para `--screenshot`,
`-profile` fresco y `--no-remote` en cada invocación). Todo contra `file://`: sin red,

## `make wpt` — benchmark axis #2: esquinas de la spec (2026-09-06)

`make parity` mide páginas REALES (la función objetivo del trabajo de render);
`make wpt` mide esquinas de la SPEC (el backlog de conformidad): un subconjunto
vendorizado de reftests CSS del WPT (`tests/wpt/`, con su `-ref.html` como fixture
de procedencia), filtrado por doctrina — estáticos o inertes-con-JS-apagado (el
arnés corre Firefox con `javascript.enabled=false`, igual que `parity`) y
autocontenidos (sin URLs remotas, sin Ahem/fuentes custom: `@font-face` se
descarta fail-closed, así que un test con fuentes mediría política, la lección de
wikipedia). Detalle del filtro y procedimiento de actualización en
`tests/wpt/README.md`.

Dos reglas de viewport hacen comparables a las páginas cortas (casi todo WPT,
donde un ratio de alturas mediría la ventana, no el documento):

- Firefox captura a `--window-size=1000,H_FD`: los dos bitmaps comparten canvas.
- `pngdiff` corre SIN su 4.º argumento (scrollHeight): `h_ratio` es 1.0 por
  construcción y el score es divergencia pura de perfiles; `H_FD` vs `FF_REAL`
  viajan como columnas informativas para que un faltante bajo el pliegue siga
  visible.

**Dado** un test WPT estático, **cuando** `make wpt` lo renderiza en los dos
motores, **entonces** PASS es score <= 5.0 y el target falla solo ante divergencia
NUEVA (score > 1.0 sobre `expected.tsv`, o test sin expectativa): un score alto
es un TODO medido, no un gate de release. `make wpt-update` congela
`build/wpt/current.tsv` → `tests/wpt/expected.tsv`.
sin estado que quede atrás.

## `make drops` — gate de descartes del parser (2026-09-11)

`--dump-css-drops` (`spec/css_drops.md`) es la otra mitad del diagnóstico: `parity`
dice cuánto difiere una página, `drops` dice qué declaraciones el parser tiró para
llegar ahí. Un `bad-value` nuevo en una página del corpus es la clase cara de bug
(la propiedad existe en todo inventario por nombre y la declaración se pierde
igual), así que es un gate, no un reporte:

- `make drops` vuelca `--dump-css-drops` de cada página de `PARITY_PAGES` y hace
  `diff -u` contra `tests/parity/drops/<page>.txt`. Cualquier diff ⇒ FAIL.
- `make drops-update` re-congela (solo con descarte justificado, igual que
  `layout-update`).

## Perfil trusted (contraste contra allowed hosts)

El corpus ya renderiza con `--author-css --images`, que es exactamente lo que la
doctrina trusted-host (`allow ∩ js ⇒ CSS de autor e imágenes efectivos`) enciende
para un host de `config/allow.conf`. Corpus cubierto por la allowlist:
`slashdot.org`, `news.ycombinator.com` (hackernews), `duckduckgo.com`,
`wikipedia.org`, `jkanime.net`. JS sigue apagado en ambos lados aunque el host
sea trusted: con JS los dos motores miden documentos distintos (lección
wikipedia-navbox, §7.4 de CLAUDE.md) y el número dejaría de calificar el layout.
