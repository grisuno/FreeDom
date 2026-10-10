# spec: webfont (`wf_`)

Pure, I/O-free `@font-face` lookahead scanner for the TRUSTED side, plus the
contract its fetch/register/select pipeline obeys. Like `prefetch`'s scanner, it
reads hostile CSS bytes without a full parser on purpose: it is a hint
extractor, never the parser of record (the worker's `css` module already parses
`@font-face` into `font_faces`). Correctness never depends on it — a missed face
falls back to the local-font stack, and every emitted URL is fetched through the
same policy-gated subresource callback as stylesheets/scripts.

## Why this exists (measured)

- jkanime ships 62 `@font-face` rules (Oswald/Mulish body text, tabler-icons);
  huggingface 89 (Charter, KaTeX, IBM Plex Mono); slashdot `sdicon`.
  Today every one renders in the local fallback: body copy sets in the wrong
  metrics (rewrap → height drift) and icon glyphs show fallback tofu.
- The formats that matter ship fallbacks: tabler-icons, sdicon, KaTeX, Charter
  and IBM Plex Mono all list `woff`/`truetype` beside `woff2`. Supporting
  `woff`/`ttf`/`otf` (FreeType-native, zero new deps) unlocks them with NO
  brotli/woff2-container work. `woff2`-only faces (jkanime Oswald/Mulish) stay
  fallback until a woff2 slice; `eot`/`svg` are never fetched (deprecated,
  Firefox can't use SVG fonts either).

## Trust model (non-negotiable)

- Fonts fetch **only for trusted pages** (`allow.conf` AND `js.conf`, the same
  `page_trusted`/`net_allowed` gate as external scripts — never for the
  `caps.images` gate alone). Rationale: a font file is parser input to
  FreeType/HarfBuzz on the TRUSTED side (unlike images, which decode inside the
  confined worker), so it follows scripts, not images. Headless: `--js=on` only.
- The worker NEVER touches font bytes and keeps fallback metrics for layout
  (zero new worker attack surface). Paint may therefore drift from layout where
  advances differ; for icon/single-glyph faces the drift is ~0, for body copy
  it is accepted v1 (documented, same class as the canvas-measure stub).
- Memory only, per-document lifetime: faces are `FT_New_Memory_Face` over owned
  buffers, freed on document teardown. Never `FcConfigAppFontAddFile` (no
  global fontconfig pollution across origins), never disk.
- Bounded: `WF_MAX_REFS` entries per scan, `WF_MAX_FACE_BYTES` per face,
  `WF_MAX_TOTAL_BYTES` per document; over → fail closed (face skipped).
- Validated, never sniffed blindly: magic bytes (`wOFF`, `\0\1\0\0`, `OTTO`,
  `true`, `typ1`) + content-type allowlist (`font/*`, `application/font-*`,
  `application/x-font-*`, `application/octet-stream`, empty like css/js).
  A mismatch fails the face, never the page.
- No `unicode-range` v1 (KaTeX splits files by range; first-face-wins per
  family+style may pick a file missing some glyph — missing glyphs fall back
  per-glyph as today), no `font-display` behavior change (render never blocks
  on a font: fallback paints first, webfont applies when bytes arrive — v1 even
  simpler: faces register before first paint of that document).

## Scope (v1)

- Scan: `@font-face` blocks → `(family, url, format, bold, italic)` per `url()`
  in `src`, in order. `font-family` unquoted or single/double-quoted (first
  name only — stacks are for selection, out of scope); `font-weight:
  bold|700..900` → bold, else regular (numeric 100..900 accepted, `normal` = 400);
  `font-style: italic|oblique` → italic. `format('woff2'|'woff'|'truetype'|
  'opentype'|'embedded-opentype'|'svg')` recorded verbatim (lowercased); no
  format hint = `""` (sniff by magic at fetch). First SUPPORTED format per
  family wins at pick time (`woff`/`truetype`/`opentype` (+ extensionless sniff);
  `woff2`/`embedded-opentype`/`svg` never picked, documented above).
- Out of scope v1: `woff2` container+brotli, `unicode-range`, `font-stretch`/
  `font-variant` descriptors, `size-adjust`, selection stacks (first family
  only), workers touching fonts, disk persistence.

## Contract

```c
#define WF_FAMILY_MAX 64
#define WF_URL_MAX    1024
#define WF_FORMAT_MAX 16
#define WF_MAX_REFS   128
#define WF_MAX_FACE_BYTES ((size_t)1u << 20)
#define WF_MAX_TOTAL_BYTES ((size_t)8u << 20)

typedef struct wf_ref {
    char family[WF_FAMILY_MAX];   /* unquoted, trimmed; "" = unusable */
    char url[WF_URL_MAX];         /* raw, unresolved (resolution is policy) */
    char format[WF_FORMAT_MAX];   /* lowercased, "" when no hint */
    int  bold;                    /* 1: weight >= 600/bold */
    int  italic;                  /* 1: italic/oblique */
    /* data: fonts (a data: URL never fits url[]): decoded at scan time into
     * owned data_bytes (is_data set, url ""); the loader registers them with
     * no fetch. Copies across lists use wf_ref_move (ownership transfer). */
    int            is_data;
    unsigned char *data_bytes;
    size_t         data_len;
} wf_ref;

typedef struct wf_list { wf_ref *refs; size_t count, cap; } wf_list;

/* Scans CSS text for @font-face blocks. Pure, reentrant, allocation only for
 * the list (owned; wf_list_free is the single idempotent NULL-safe releaser).
 * Returns 0 (empty list when nothing usable), -1 on NULL args only. */
int wf_scan(const char *css, size_t len, wf_list *out);
void wf_list_free(wf_list *l); /* idempotent, NULL-safe */

/* 1 when fmt names a fetchable format (woff/truetype/opentype, ci) or carries
 * no hint at all ("" — the picker then sniffs magic at receipt, failing closed
 * on mismatch); 0 for woff2/eot/svg/NULL. Pure. */
int wf_supported_format(const char *fmt);
```

## Fetch-and-register pass (b3a, `webfont_load`)

`wf_load_document(fetch, fctx, page_url, extern_sheets, nextern, html, html_len)`:
extern sheets in order, then inline `<style>` bodies in document order (same
order as the worker sheet, extern-then-inline, so first-wins agrees).

- Per (family, bold, italic) key: first SUPPORTED format wins; unsupported
  hints skip without consuming the key; up to `WF_LOAD_TRIES_PER_KEY` URLs per
  key fall back in src-list order; `WF_LOAD_MAX_FETCHES` fetches per document.
- Resolution: absolute https as-is; relative against the sheet's own URL
  (extern) or page URL (inline), https-only (`url_resolve_https`); anything
  else skipped. `data:` URLs never fit `url[]`: the scanner decodes them at
  scan time into owned `data_bytes` on the ref (`is_data`), capped at
  `WF_DATA_URL_MAX` pre-decode; the loader registers them with no fetch.
  Struct copies across lists use `wf_ref_move` (ownership transfer — a shallow
  copy double-frees under ASan).
- Receipt checks (https only): status 2xx, `ctype_ok` (font/*,
  application/font-*, application/x-font-*, octet-stream, empty), size caps
  (`WF_MAX_FACE_BYTES` each, `WF_MAX_TOTAL_BYTES` total). Registration
  re-validates magic and parseability (`tsh_webfont_register` fails closed).
- `fetch == NULL` (untrusted page: the caller passes no fetcher) ⇒ `-1`,
  zero faces, zero calls. Returns faces registered otherwise.

## Given-When-Then

1. **Dado** `@font-face{font-family:'X';src:url(a.woff2) format('woff2'),url(a.woff) format('woff');}` **cuando** se escanea **entonces** hay 2 refs (`X`, urls en orden, formats `woff2`/`woff`) y el picker posterior elige `a.woff`.
2. **Dado** `font-weight:700` / `font-style:italic` **entonces** `bold`/`italic` = 1; **dado** `400`/`normal` **entonces** 0.
3. **Dado** `@font-face` sin `src` con `url()` (solo `local(...)`) **entonces** cero refs (nunca toca disco local por nombre: mismas razones anti-fp que `document.fonts`).
4. **Dado** bytes hostiles arbitrarios **cuando** se escanean **entonces** sin crash/UB/OOM (fuzzeado), lista acotada a `WF_MAX_REFS`, sin I/O.
5. **Dado** `url()` de más de `WF_URL_MAX` **entonces** esa entrada se descarta (fail closed), el resto sobrevive.
6. **Dado** el mismo texto con y sin escaneo **entonces** el render sin caras registradas es byte-idéntico (el scanner no cambia nada por sí solo).

## Tabla de errores

| Condición | Resultado |
| :-- | :-- |
| `css`/`out` NULL | `-1` |
| Bloque sin `font-family` o sin `url()` | sin refs (no es error) |
| Más de `WF_MAX_REFS` entradas | se queda con las primeras, resto ignorado |
| `local()` como única fuente | sin refs |

## Del nombre al píxel: la cadena del hash (b2)

El pintor necesita saber QUÉ familia pide cada run, pero la cascada solo
retenía el bucket genérico. La cadena, toda con el mismo hash:

1. **Parse** (`css.c`): `font-family`/`font` emiten, junto al bucket, un slot
   `P_FONTFACE` con el PRIMER nombre en el pool compartido de strings
   (wide keywords reclaman ambos slots sin escribir; pool lleno degrada a
   `ival=-1`, nunca a drop — misma doctrina que `content`).
2. **Cascade** (`apply_decl`, con `sheet`): el nombre se compara
   case-insensitive con las `font_faces` de la sheet; match ⇒
   `css_style.fontface = wf_name_hash` (0 = ninguna). Sin sheet (inline-only),
   sin pool o sin match ⇒ 0; el bucket sigue mandando.
3. **Runs** (`page_view`): `pv_text_ext.fontface` hereda como `font_family`;
   `pv_run.fontface` viaja en cada run (setter existente, sin IPC nuevo aquí).
4. **Doc** (`render_doc`): `rd_block.fontface` con el mismo gate `caps.css`.
5. **IPC** (`tab.c`): `b[57]`, `TAB_WIRE_B_N` 57→58, `make drift` lo ata.
   Bits intactos (unsigned→int32→unsigned).
6. **Caras** (`text_shape`): `tsh_webfont_register` valida (magic, topes,
   `FT_New_Memory_Face`) y guarda por (hash, bold, italic); `tsh_font.wfh`
   selecciona cara registrada antes que el bucket local; miss ⇒ bucket
   (fail-visible, nunca fail-hard); `tsh_webfont_clear` por documento.

`wf_name_hash` (FNV-1a 32, lowercased, 0 reservado) vive `static inline` en
`webfont.h` para no añadir aristas de link al lado worker.

## Lección del retry (bug latente encontrado por esta tanda)

`add_rule` reintentaba con poco slack restaurando `n`/`total` del drop log
pero NO los `count` de buckets preexistentes (ni los cursores de pools):
una regla reintentada sobre-contaba exactamente esos buckets
(`transition-property` 5→6 con el total intacto). El fix snapshottea ambos en
el path raro (heap, sin VLA) + test determinista que llena el array a
`room=44` (`test_drops_retry_rewinds_buckets`, rojo-sin-fix verificado).

## Seguridad

- Sin I/O, sin estado global, reentrante; el llamante posee la lista.
- Todo copiado acotado con NUL; sin `sscanf`/`strcat` en la ruta hostil.
- La superficie голода: `wf_scan` + `wf_supported_format` + `wf_list_free`.
- El fetch/parse de bytes vive en la fase b2 con su propio threat model
  (policy gate, magic, topes, fuzz de `FT_New_Memory_Face`).
