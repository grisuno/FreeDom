# `text_shape` (`tsh_`) — HarfBuzz text shaping for the painter

> **Hito 25 — Correct text shaping.** Replaces the Cairo *toy* font API
> (`cairo_select_font_face` + `cairo_show_text`, which lays out one glyph per
> byte with no script awareness) with HarfBuzz shaping + Cairo's glyph API
> (`cairo_show_glyphs`). This brings ligatures, GPOS kerning, contextual forms
> and correct intra-run direction for complex scripts (Arabic/Hebrew cursive
> joining, Indic reordering) to rendered page text.

## 0. Where it runs (zero-trust placement)

This module is a **trusted-side rendering helper**. It is linked into and called
**only** by the painters (`gui/browser_ui.c`, and through it the headless
`--download-pdf` path). It is **never** linked into nor called by the confined
worker (`tab`/`renderer` child): that child re-execs `/proc/self/exe` and runs
`tab_worker_dispatch` as the first statement of `main`, before any Cairo /
fontconfig / HarfBuzz state exists, then drops into seccomp+Landlock. The worker
keeps producing **inert display lists** (`pv_run` → `rd_block`); it never shapes
or touches a font.

The two inputs of shaping have different trust levels, and the split is the
security argument for this placement:

- **Text** — `[text, len)` is **hostile remote content** (page text), already
  sanitised to UTF-8 by `page_view`'s transcoder, but still attacker-influenced.
  HarfBuzz has had CVEs in its shaping path, so this entry is **fuzzed**
  (`make fuzz-tsh`) exactly like every other module that touches remote bytes.
- **Fonts** — resolved from the **local** system via fontconfig and parsed by
  FreeType. These are trusted, exactly the files Cairo's toy API already opened.
  No author `@font-face`/web font is ever fetched or used (Privacy by Default;
  the CSS layer already drops `url(` and `@font-face`). Shaping **never** opens a
  socket, reads navigation state, or persists anything (Zero Knowledge intact).

This placement does **not** weaken any sandbox boundary: the worker boundary is
unchanged, and parsing local fonts on the trusted side is what Cairo already did.

## 1. Public API (`include/text_shape.h`)

```c
typedef struct tsh_font { int family; int bold; int italic; } tsh_font;

#define TSH_MAX_GLYPHS 4096u          /* anti-DoS cap on one shaped slice  */
#define TSH_MAX_TEXT   (1u << 20)     /* 1 MiB cap on one shaped slice     */

typedef enum tsh_status {
    TSH_OK = 0,
    TSH_ERR_UNAVAIL,   /* backend/font unavailable -> caller uses toy fallback */
    TSH_ERR_INPUT,     /* null/oversize args (fail-closed)                     */
    TSH_ERR_OVERFLOW,  /* glyph count would exceed cap (fail-closed)           */
} tsh_status;

int        tsh_ready(void);           /* 1 once a fallback font resolves (lazy) */
tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,
                     cairo_glyph_t *out, size_t cap, size_t *out_n, double *out_adv);
double     tsh_measure(const tsh_font *f, double px, const char *text, size_t len);
tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,
                    double x, double baseline, const char *text, size_t len);
void       tsh_shutdown(void);        /* release cached faces/library (leak hygiene) */
```

- `family` is a `css_font_family` bucket (`CSS_FF_*`): the engine matches the
  **generic** group only (serif / sans / mono / cursive / fantasy), never an
  exact author family — consistent with `family_face()` in the painter.
- `px` is the pixel size already scaled by the page zoom.
- `tsh_shape` writes glyph positions relative to **origin (0,0)** on the
  baseline; the caller offsets by its pen `(x, baseline)`. `*out_adv` is the
  total pen advance in pixels (subpixel, from HarfBuzz 26.6 positions / 64).
- **Not thread-safe**: a single static scratch buffer and a global face cache
  serve the single-threaded painter. The confined worker never calls it.

## 2. Behaviour — Given/When/Then

### Availability and fallback
- **Given** a host with at least one resolvable system font, **when** any
  `tsh_*` is first called, **then** `tsh_ready()` lazily resolves and caches the
  sans/UNSET face and returns 1.
- **Given** a host where fontconfig resolves no font (or FreeType fails),
  **when** `tsh_ready()` is called, **then** it returns 0 and every `tsh_shape`/
  `tsh_draw` returns `TSH_ERR_UNAVAIL` and `tsh_measure` returns `< 0.0`. The
  painter then uses its existing toy-API path: **byte-identical to the
  pre-Hito-25 renderer**. No regression on font-less hosts.

### Shaping
- **Given** the ASCII string `"Hello"` in sans at 16px, **when** `tsh_shape` is
  called, **then** it returns `TSH_OK`, `*out_n == 5`, every glyph advance is
  `> 0`, the cumulative x positions are non-decreasing, and `*out_adv` equals
  the position past the last glyph.
- **Given** an empty slice (`len == 0`), **when** `tsh_shape` is called, **then**
  it returns `TSH_OK` with `*out_n == 0` and `*out_adv == 0.0` (no write to
  `out`).
- **Given** the same `(font, px, text)` twice, **when** shaped, **then** the
  glyph ids, positions and advance are **identical** (determinism — required so
  the layout-time measure and the paint-time draw never disagree).
- **Given** a font and text that ligate (e.g. `"ﬁ"`-forming `"fi"` in a font
  with the `liga` feature), **then** `*out_n < byte count` is **allowed**
  (ligature collapse); the contract guarantees only the bound/positivity
  invariants, not a specific glyph count for ligating input.

### Caps and fail-closed
| Condition | Result |
| :-- | :-- |
| `f == NULL` / `text == NULL` (with `len>0`) / `out == NULL` (shape) / `out_n`/`out_adv` NULL | `TSH_ERR_INPUT`, no write |
| `len > TSH_MAX_TEXT` | `TSH_ERR_INPUT` |
| `px <= 0.0` or non-finite | `TSH_ERR_INPUT` |
| `cap == 0` | `TSH_ERR_INPUT` |
| shaped glyph count `> cap` or `> TSH_MAX_GLYPHS` | `TSH_ERR_OVERFLOW`, no partial result the caller relies on |
| backend/font unavailable | `TSH_ERR_UNAVAIL` |

On any non-`TSH_OK` status the caller (`tsh_measure` → `< 0`, `tsh_draw` →
status) **falls back to the toy path**, so measure and draw stay consistent for
that slice (both toy).

## 3. Internals

- One shared `FT_Library` and the default `FcConfig`, lazily initialised.
- A small fixed cache of faces keyed by `(family, bold, italic)` — at most
  `5 families × 2 weights × 2 slants = 20` entries. Each entry owns: the font
  file bytes (read once into memory; FreeType's memory face does not copy), an
  `FT_Face`, a `cairo_font_face_t` (via `cairo_ft_font_face_create_for_ft_face`),
  and an independent `hb_face_t`/`hb_font_t` built from the same bytes
  (`hb_blob` → `hb_face` → `hb_font`). Cairo and HarfBuzz parse the **same font
  program**, so glyph ids agree; the two objects share no mutable FreeType state.
- Per shape: `hb_font_set_scale(px*64)`, reset the cached `hb_buffer`,
  `hb_buffer_add_utf8`, `hb_buffer_guess_segment_properties` (auto script /
  direction / language from the run), `hb_shape`, then translate HarfBuzz
  positions (26.6) into `cairo_glyph_t` (px). `tsh_draw` sets the cached cairo
  FT face + size and calls `cairo_show_glyphs` with the current source.
- All allocations live in process globals (the cache); there is **no
  per-call persistent allocation**, so leak detection over the shaping path is
  meaningful (fontconfig's own one-time leaks are already suppressed in
  `tests/asan.supp`).

## 4. Integration in the painter (`gui/browser_ui.c`)

`content_font()` additionally records the current `(family,bold,italic)` and
px into file-static state (the single-threaded painter always selects the font
before measuring/drawing). The two atomic text primitives become
shaping-backed with a toy fallback:

- `measure_slice()` → `tsh_measure(key, px, s, n)`; on `< 0` fall back to
  `cairo_text_extents`.
- `draw_slice()` (now taking the `(x, baseline)` origin) → `tsh_draw(...)`; on
  non-`TSH_OK` fall back to `cairo_move_to` + `cairo_show_text`.

Because `styled_advance`/`styled_draw` both route through these primitives, the
whole-slice fast path gains full word-level shaping, while the per-cluster path
(text-transform / letter-spacing) shapes each cluster individually — which
matches CSS semantics (letter-spacing disables ligatures). Layout measure and
paint draw call the same shaper on the same slice, so positions stay consistent.

## 5. Out of scope (v1)

- **Full bidi** (Unicode Bidirectional Algorithm across runs / mixed-direction
  paragraphs). v1 shapes per word/run with HarfBuzz's per-run direction guess;
  paragraph-level reordering of mixed LTR/RTL is deferred.
- **Font fallback chains** for missing glyphs (one face per generic bucket; a
  codepoint absent from that face renders as `.notdef`/tofu, as today). A
  fontconfig fallback walk is a follow-up.
- **Exact author family matching** and web fonts (`@font-face`) — forbidden by
  Privacy by Default; the CSS layer already drops them.
- **Shaping in the headless flat renderers** (`gui/ui_render.c`, the
  `renderer.c` confined parser produces no pixels). The box-aware painter
  (`browser_ui.c`) — the one reused by `--download-pdf` and the GUI — is the
  target; the flat freedom-view path keeps the toy API for now.
- **Cross-word shaping / justification.** Word is the shaping granularity, which
  is correct for cursive scripts (joining happens within a word) and matches the
  existing whitespace-split flow.

## 6. Verification

1. Spec (this file).
2. Red test: `tests/test_text_shape.c` (CMocka) before `src/text_shape.c`.
3. Green: `src/text_shape.c`.
4. Refactor (DRY the measure/draw primitives behind the shaper; toy fallback).
5. `make asan` clean (fontconfig leaks suppressed; no per-call leak).
6. `make fuzz-tsh` — arbitrary bytes as the shaped text must never crash/leak/UB
   nor exceed the glyph cap nor write OOB.
7. Visual review: `--download-pdf` of a page with Latin + a ligating pair +
   (if a font is present) an Arabic/Hebrew word, rasterised to PNG and read.
8. Docs: this spec, `CLAUDE.md` hito, `docs/index.html`, `README.md`, memory.
