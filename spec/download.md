# spec: download (`dl_`)

Pure, I/O-free helpers for "save this resource to disk". When the user follows a
link to a non-renderable resource (a PDF, an archive, an e-book) or explicitly
asks to save the current page, Freedom writes the fetched bytes to a file under
`~/Downloads/freedom/` instead of trying to render them. The disk I/O and the
directory creation are the GUI orchestrator's job; what lives here is the
directly auditable surface:

  1. **The output filename is derived from hostile remote input** — the
     `Content-Disposition` header and the URL path are attacker-controlled. A
     name like `../../.bashrc`, with control bytes, path separators or a hidden
     leading dot, must never escape the download directory or name an arbitrary
     file. Secure by Default / fail closed: an unsafe name is not representable.
  2. **The render-vs-download decision** (is this response a page or an
     attachment?) is a small classification that must be testable without a
     network or a screen.
  3. **The size cap** (refuse an unbounded download) is pure arithmetic.

Pure, reentrant, no global state. Reuses `pe_safe_basename` (pdf_export) as the
single sanitizer so the audited fail-closed rule lives in exactly one place.

## Constants

| Macro | Value | Meaning |
| :-- | :-- | :-- |
| `DL_NAME_MAX` | 128 | Max bytes of the sanitized name (matches `PE_NAME_MAX`). |
| `DL_FALLBACK_NAME` | `"download"` | Used when neither disposition nor URL yields a usable name. |
| `DL_MAX_BYTES` | 256 MiB | Hard cap; a larger body is refused (anti-DoS / fail closed). |

## Errors (`dl_status`)

| Code | Meaning |
| :-- | :-- |
| `DL_OK` | Success. |
| `DL_ERR_NULL_ARG` | A required pointer was NULL / `outsz == 0`. |
| `DL_ERR_OVERFLOW` | The result did not fit `out`; `out` left empty (fail closed). |
| `DL_ERR_TOO_LARGE` | The body exceeds `DL_MAX_BYTES`. |

## API

### `int dl_should_download(const char *content_type, const char *content_disposition)`

Returns 1 when the response should be saved rather than rendered, 0 when it
should be rendered. Rules, in order:

- `content_disposition` contains the token `attachment` (case-insensitive) => 1.
- Otherwise the media type of `content_type` (the part before any `;`, trimmed,
  lowercased) is classified:
  - renderable (=> 0): empty / NULL, `text/html`, `application/xhtml+xml`,
    `text/plain`, or any `text/*`.
  - everything else (`application/pdf`, `application/zip`,
    `application/octet-stream`, `image/*`, ...) => 1.

Fail-safe default: an unknown/binary type downloads (it would render as garbage),
but a missing type renders (preserves today's behavior for servers that omit it).

### `const char *dl_ext_for_type(const char *content_type)`

Returns a conventional dotted extension (`".pdf"`, `".zip"`, `".epub"`,
`".txt"`, `".json"`, `".png"`, `".jpg"`, `".gif"`, `".svg"`, `".gz"`, `".tar"`)
for a known media type (params stripped, case-insensitive), or `""` for an
unknown one. The returned pointer is a static string literal (never freed). Used
only to supply an extension when the derived name has none.

### `dl_status dl_pick_name(const char *url, const char *content_disposition, const char *content_type, char *out, size_t outsz)`

Derives a safe download filename into `out`. Candidate, in priority order:

  1. the `filename=` / `filename*=` value of `content_disposition` (quotes
     stripped; for `filename*=charset''v` the part after `''`; not
     percent-decoded);
  2. the last path segment of `url` (query `?...` and fragment `#...` removed);
  3. `DL_FALLBACK_NAME`.

The candidate is sanitized with `pe_safe_basename` (keeps only `[A-Za-z0-9._-]`,
maps every other byte to `_`, collapses `_` runs, trims `_`/`.`/`-`, no path
separators, no leading dot, no traversal). If the candidate contributes no
alphanumeric byte, `DL_FALLBACK_NAME` is used instead. If the sanitized name has
no extension and `content_type` maps to one via `dl_ext_for_type`, that extension
is appended (when it fits). The result is always non-empty and NUL-terminated on
`DL_OK`. `url == NULL` and `content_disposition == NULL` are treated as absent.
`out == NULL` / `outsz == 0` => `DL_ERR_NULL_ARG`; a name that cannot fit (even
without the extension) => `DL_ERR_OVERFLOW` (`out` left empty).

### `dl_status dl_build_path(const char *dir, const char *name, char *out, size_t outsz)`

Builds `dir` + `"/"` + `name` into `out`. `dir` is trusted (chosen by the app
from `$HOME`/XDG); `name` MUST already be a sanitized basename. A trailing `/`
on `dir` is respected (not duplicated). Defensively rejects a `name` that still
contains `/` (=> `DL_ERR_OVERFLOW`) so a path can never escape `dir`. Fails
closed on overflow (`out` left empty). `dir`/`name`/`out` NULL or `outsz == 0`
=> `DL_ERR_NULL_ARG`.

### `dl_status dl_check_size(size_t len)`

`DL_OK` if `len <= DL_MAX_BYTES`, else `DL_ERR_TOO_LARGE`. Trivial guard the
orchestrator calls before writing.

## Guarantees

- **No traversal, by construction.** The name comes only from `pe_safe_basename`
  (no `/`, no leading dot, no `..`), and `dl_build_path` re-checks for `/`. The
  written path is always a direct child of the trusted directory.
- **Always names something.** A hostile or empty candidate degrades to
  `DL_FALLBACK_NAME` (+ a type extension), never to nothing.
- **Bounded.** Every write is length-checked; overflow fails closed (empty out),
  size fails closed (`DL_ERR_TOO_LARGE`).
- **Pure.** No allocation, no I/O, no global state; reentrant.

## Out of scope

- The actual file write, directory creation, atomic rename, and 0600 perms (GUI
  orchestrator, mirroring `disk_store`'s atomic-write convention).
- Resume / range requests, concurrent downloads, a download manager UI.
- Percent-decoding / RFC 5987 charset decoding of `filename*=` (the raw value is
  sanitized, which is safe; it just may keep `%xx` literally).
- MIME sniffing of the body (we trust the server's declared type only to choose
  render-vs-save and an extension; we never execute or trust the content).
