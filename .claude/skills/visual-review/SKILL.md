---
name: visual-review
description: "Visually review Freedom's GUI rendering without a Wayland display: export a page to a PNG headless with `freedom --download-png=PATH` and Read the image to verify text/layout/colours/artifacts. Use when validating any render/layout/CSS/image change (CLAUDE.md §3 validation step), comparing before/after, or checking a URL or local HTML file paints correctly."
trigger: /visual-review
---

# /visual-review — Freedom render verification (headless)

Freedom's on-screen renderer needs Wayland, which is not available to an automated
agent in this environment. `freedom --download-png=PATH` exports the **exact same
display list the GUI would paint** to a single PNG bitmap (no window), so the render
can be inspected by just `Read`-ing the image. This is the validation step that
`CLAUDE.md` §3 makes mandatory for render/layout/CSS/image work.

**Prefer PNG over PDF.** A PNG is a single image read in one step — far cheaper (fewer
tokens) than a PDF, which must first be rasterised with `mutool` (or read page-by-page).
Use `--download-pdf` only when you specifically need the vector document (selectable
text, real pagination), not for routine visual review.

The PNG path is the *same* code as the GUI "Save as PNG"/"Save as PDF" (`write_doc_png`/
`write_doc_pdf` → `layout_doc`/`paint_content_row`), so what you see is what the window
paints, minus images (off by default — they appear as labelled placeholders unless
enabled).

## Prerequisites

- A built binary: `make` (use `./build/freedom`, not a stale `freedom` on `PATH`).
- Nothing else for PNG. (PDF fallback only: `mutool` from mupdf-tools.)

## Steps

Use the session scratchpad for the image (never `/tmp` directly, never the repo tree).
Let `$SP` be the scratchpad directory given in the environment.

1. **Export the page to PNG** (a URL, or a local `.html` file):

   ```
   ./build/freedom --download-png=$SP/frame.png <URL-or-file.html>
   ```

   stdout is one line: `Saved PNG (<h> px): <path>`. Exit 0 = ok; exit 1 = nothing to
   render / write error; exit 2 = usage error (e.g. `--download-png` with no `=PATH`).
   For a page that needs Tor/I2P or weak TLS, add the usual flags
   (`--tor`, `--i2p`, `--insecure`); JS with `--js=on`; author CSS with `--author-css`.

   The PNG is one continuous bitmap of the whole page (1000px wide; height follows the
   content, capped at 30000px — a taller page is clipped).

2. **Read the image** with the Read tool: `Read $SP/frame.png`. Done.

3. **Verify** against the rendering checklist (below). State findings plainly; if a
   reference screenshot exists for this page, compare against it.

### PDF fallback (only when you need the vector document)

```
./build/freedom --download-pdf=$SP/frame.pdf <URL-or-file.html>
mutool draw -r 96 -o $SP/frame-%d.png $SP/frame.pdf   # one PNG per page
```

If `mutool` is unavailable, `Read $SP/frame.pdf` with the `pages` parameter.

5. **Optional — enable what's off by default** to review more:
   - Author colours/CSS and images are off by default (Privacy by Default). The headless
     export uses the safe caps, so author colours and images show as the theme/placeholder.
     To review them, that capability has to be turned on in the render path being tested
     (see `render_doc`/`rdp_caps`); note this in your findings rather than assuming the
     page is broken.

## Rendering checklist

- **Text** legible, correctly wrapped, no overlap with neighbouring blocks.
- **Block layout**: headings vs paragraphs vs lists vs tables positioned sensibly; list
  markers (`•`/`N.`) and indentation present; table cells form a grid (columns aligned).
- **Inline emphasis**: `b/strong` bold, `i/em` italic; links coloured + underlined.
- **Colours/theme**: the export is dark-on-white (forced light theme for print/raster);
  banners (tracking warning) and form buttons painted with their theme colours.
- **Images**: with images off, a bordered placeholder labelled with the
  render_policy decision (`image blocked: …`) — never a remote fetch.
- **Artifacts**: no clipped text, no garbled glyphs (accents should survive — CP-1252→UTF-8),
  no missing rows, pagination doesn't split a row mid-line.

## One-shot helper (export + read)

```
URL="$1"; OUT="${2:-$SP/frame}"
./build/freedom --download-png="$OUT.png" "$URL" && echo "Read $OUT.png"
```

## Notes

- `--download-png=PATH` / `--download-pdf=PATH` use PATH verbatim (a trusted local CLI
  argument). The fail-closed sanitisation of a hostile page *title* into a filename
  (`pe_safe_basename`/`pe_build_path_ext`) applies only to the GUI "Save as PNG/PDF",
  where the name comes from remote content.
- The export touches no network beyond fetching the page itself; nothing is cached or
  phoned home. Local files get a `file://` origin (relative images confined to the doc
  directory).
- LSan reports one-time `libfontconfig` allocations as leaks when running an ASan build
  directly; they are suppressed by `tests/asan.supp` (`make asan` is clean).
