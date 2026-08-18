---
name: pngprof
description: "Print the structural ink profile of a rendered screenshot as text: make pngprof PNG=file.png. Shows where ink sits horizontally (column profile per vertical band) and how it is distributed down the page (cumulative). Use when comparing Freedom's render against Firefox (or any reference PNG) and image input is unavailable, or when the numbers matter more than the picture."
trigger: /pngprof
---

# /pngprof — structural ink profile of a screenshot

Companion to `/visual-review` and `make parity`. When you cannot Read an image
(no image input) or when a divergence needs a NUMBER, this prints where the ink
sits in any rendered PNG:

- `width height bg` — the image size and the modal background luminance the ink
  threshold was measured against.
- the **column profile**: `ncols` horizontal buckets rendered as `# + .` glyphs,
  one row per vertical band (default 3 bands). `#` = dense ink (a text column),
  `+` = present, `.` = sparse, space = empty.
- the **cumulative vertical ink** distribution over `nrows` bands (0..1).

## Usage

```
make pngprof PNG=build/parity/slashdot.ff.png
make pngprof PNG=x.png BANDS=4 COLS=200 ROWS=20
python3 tools/pngprof.py x.png            # direct (same flags)
```

The target lives in the Makefile (`make pngprof`), the implementation in
`tools/pngprof.py` (pure python, zero dependencies, no network).

## Workflow (the loop `make parity` is missing)

1. Run `make parity` — pngdiff says HOW MUCH a page diverges (score).
2. Produce the two screenshots the harness already made:
   `build/parity/<page>.fd.png` (Freedom) and `<page>.ff.png` (Firefox).
3. `make pngprof PNG=build/parity/<page>.fd.png` and the same for the Firefox
   PNG — two text dumps.
4. Read the two profiles side by side: a column that wraps too early shows a
   narrower ink span; a sidebar that failed to pull up shows the rail's columns
   empty in the top band and lit below; a full-width article shows ink reaching
   the right edge where the reference stops at the reserved gap.

Reading the profile of the REFERENCE is the cheap substitute for reading the
image itself: the glyph map IS the layout.

## Notes

- The decoder is a pure-python PNG reader (zlib + the five filters). RGBA, RGB,
  grey and 16-bit inputs all normalise.
- Ink = pixels whose luminance differs from the modal background by more than 24
  (the same definition as `tools/pngdiff.c`), so themes compare.
- Freedom screenshots come from `./build/freedom --download-png=PATH --author-css
  --images <page>`; Firefox ones from `firefox --headless --no-remote --profile
  <fresh profile> --screenshot PATH --window-size=1000 file://<page>` (the two
  traps documented on the `parity` target apply).
