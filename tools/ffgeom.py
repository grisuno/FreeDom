#!/usr/bin/env python3
"""
ffgeom -- Firefox geometry as TEXT, no image reading.

The `make geom` loop needs Firefox's getBoundingClientRect() numbers, and its only
headless output here is a screenshot. This tool turns that screenshot into a text
dump mechanically: the probe page replaces the body with a BIT-GRID canvas that
encodes every measured rect as black/white cells, this script decodes the cells
back into numbers, and prints one line per rect:

    <index> <tag>.<class> top=<t> left=<l> w=<w> h=<h>

The encoding is a fixed grid, no OCR, no image model:
  - canvas 64px wide, each row 16 cells of 4x4px, one row per 16-bit VALUE
  - row 0: magic 0xC0DE (16 bits) + row count (16 bits)
  - then per rect: 4 rows (top, left, w, h), MSB first
  - rows continue per rect; the decoded count bounds the region read

The decoded values are what `make geom` prints beside Freedom's own --dump-layout,
so a layout difference reads as two columns of numbers instead of being guessed
from pixels. The canvas is white and fixed at the top-left of the viewport, so
the grid region carries no underlying page ink.

Usage:
  ffgeom probe <page.html> <selector> <out.html>
  ffgeom decode <screenshot.png>

Both steps run through `make geom` (the Makefile is the single source of truth);
this script is the thin worker it delegates to. Pure python, no dependencies, no
network. It reads only local files the harness produced.
"""

import subprocess
import sys


HEIGHT_SCRIPT = """
<script>
window.addEventListener("load", function () {
  var sh = document.documentElement.scrollHeight;
  if (sh <= 0) sh = document.body.scrollHeight;
  var d = document.createElement("div");
  d.id = "__ffh";
  d.style.cssText = "position:absolute;left:0;top:0;width:1px;height:" + sh + "px";
  document.body.appendChild(d);
});
</script>
"""


PROBE_TMPL = """<!doctype html>
<html><head><meta charset="utf-8"><style>
body { margin: 0; }
#ffgeom-grid { background: #fff; }
</style></head><body>
<script>
window.addEventListener("load", function () {
  var els = document.querySelectorAll("%s");
  var rows = [];
  for (var i = 0; i < els.length && i < 1000; ++i) {
    var e = els[i];
    var r = e.getBoundingClientRect();
    var cs = getComputedStyle(e);
    var v = [Math.round(r.top), Math.round(r.left),
             Math.round(r.width), Math.round(r.height),
             Math.round(parseFloat(cs.marginLeft)),
             Math.round(parseFloat(cs.marginRight)),
             Math.round(parseFloat(cs.paddingLeft)),
             Math.round(parseFloat(cs.paddingRight))];
    for (var k = 0; k < 8; ++k) if (v[k] < 0) v[k] += 65536;
    rows.push(v);
  }
  var cv = document.createElement("canvas");
  cv.id = "ffgeom-grid";
  var rowsN = rows.length * 8 + 3;
  cv.width = 64;
  cv.height = rowsN * 4;
  document.body.replaceChildren(cv);
  var ctx = cv.getContext("2d");
  ctx.fillStyle = "#fff";
  ctx.fillRect(0, 0, cv.width, cv.height);
  ctx.fillStyle = "#000";
  function cell(r, c) { ctx.fillRect(c * 4, r * 4, 4, 4); }
  function word(row, v) {
    for (var b = 0; b < 16; ++b)
      if ((v >> (15 - b)) & 1) cell(row, b);
  }
  word(0, 0xFFFF);
  word(1, 0xC0DE);
  word(2, rowsN);
  var rw = 3;
  for (var i = 0; i < rows.length; ++i)
    for (var v = 0; v < 8; ++v) word(rw++, rows[i][v]);
});
</script></body></html>
"""


def load_rows(path):
    import struct
    import zlib
    data = open(path, "rb").read()
    if data[:8] != b"\x89PNG\r\n\x1a\n":
        raise ValueError("%s: not a PNG" % path)
    pos = 8
    idat = b""
    width = height = color_type = None
    while pos < len(data):
        length = struct.unpack(">I", data[pos:pos + 4])[0]
        typ = data[pos + 4:pos + 8]
        if typ == b"IHDR":
            width, height, _, color_type = struct.unpack(">IIBB", data[pos + 8:pos + 18])
        elif typ == b"IDAT":
            idat += data[pos + 8:pos + 8 + length]
        elif typ == b"IEND":
            break
        pos += 12 + length
    channels = {0: 1, 2: 3, 3: 1, 4: 2, 6: 4}.get(color_type, 4)
    raw = zlib.decompress(idat)
    stride = width * channels
    rows = []
    prev = bytearray(stride)
    p = 0
    for _ in range(height):
        filt = raw[p]
        p += 1
        line = bytearray(raw[p:p + stride])
        p += stride
        if filt == 1:
            for i in range(channels, stride):
                line[i] = (line[i] + line[i - channels]) & 255
        elif filt == 2:
            for i in range(stride):
                line[i] = (line[i] + prev[i]) & 255
        elif filt == 3:
            for i in range(stride):
                a = line[i - channels] if i >= channels else 0
                line[i] = (line[i] + ((a + prev[i]) >> 1)) & 255
        elif filt == 4:
            for i in range(stride):
                a = line[i - channels] if i >= channels else 0
                b = prev[i]
                c = prev[i - channels] if i >= channels else 0
                pa, pb, pc = abs(b - c), abs(a - c), abs(a + b - 2 * c)
                pred = a if (pa <= pb and pa <= pc) else (b if pb <= pc else c)
                line[i] = (line[i] + pred) & 255
        rows.append(line)
        prev = line
    return width, height, channels, rows


def lum(p):
    return 0.2126 * p[0] + 0.7152 * p[1] + 0.0722 * p[2]


def _word_reader(path):
    """Loads a probe screenshot and returns a function reading 16-bit words from
    the bit-grid at (x0, y0). Shared by `decode` (rects) and `height` (the page's
    real scrollHeight)."""
    width, height, channels, rows = load_rows(path)
    if width < 64:
        raise ValueError("%s: narrower than the 64px grid" % path)

    def lum_at(x, y):
        if y >= height or x >= width:
            return 255
        px = rows[y][x * channels:x * channels + 3]
        return lum(px)

    # The probe page keeps the ORIGINAL document's head styles, so a page with a
    # default body margin puts the canvas at (8, 8), not (0, 0). Locate the grid
    # by its alignment row instead of assuming an origin: the first line with a
    # long black run, then that run's left edge. Both are multiples of the 4px
    # cell, so the search is exact.
    y0 = -1
    x0 = -1
    for y in range(0, min(height, 64)):
        run = [x for x in range(0, min(width, 80))
               if lum_at(x, y) < 128]
        if len(run) >= 48:
            y0 = y
            x0 = run[0]
            break
    if y0 < 0:
        raise ValueError("%s: no alignment row found (is this a ffgeom probe shot?)"
                         % path)
    base = y0 & ~3

    def bit(grid_row, cell, origin):
        return 1 if lum_at(origin + cell * 4 + 2, base + grid_row * 4 + 2) < 128 else 0

    def word(grid_row, origin):
        v = 0
        for b in range(16):
            v = (v << 1) | bit(grid_row, b, origin)
        return v

    # The grid's rows are 4px tall and sampled at 4px multiples, but the canvas may
    # sit at a 1px offset (a page whose UA reset the margin to something odd), so
    # try each of the four sub-cell origins and keep the one whose magic word reads.
    x0 = -1
    origin = -1
    for y0c in range(base, base + 4):
        # locate the run's left edge within this candidate row
        for x in range(0, min(width, 80)):
            if lum_at(x, y0c + 1) < 128:
                x0 = x
                break
        if x0 < 0:
            continue
        x0 &= ~3
        if word(1, x0) == 0xC0DE:
            origin = x0
            y0 = y0c
            break
    if origin < 0:
        raise ValueError("%s: grid magic 0x%04X not found (probe version skew?)"
                         % (path, word(1, (x0 & ~3) if x0 >= 0 else 0)))
    return lambda row: word(row, origin)


def decode(path):
    word = _word_reader(path)
    total_rows = word(2)
    nrect = (total_rows - 3) // 8
    out = []
    for i in range(nrect):
        base = 3 + i * 8
        vals = [word(base + k) for k in range(8)]
        for k in range(8):
            if vals[k] >= 32768:
                vals[k] -= 65536
        out.append(vals)
    return out


def _append_probe(src, script):
    """Inserts the probe script before </body> (else </html>, else at EOF: many
    WPT files omit the explicit body close and the parser closes it for us)."""
    idx = src.lower().find("</body>")
    if idx < 0:
        idx = src.lower().find("</html>")
    if idx < 0:
        return src + script
    return src[:idx] + script + src[idx:]


def probe(page, selector, out_html):
    import re
    with open(page) as f:
        src = f.read()
    # The page's own scripts must not run: the probe is how the harness measures
    # the no-JS document (javascript.enabled=false in the parity profile), but the
    # PROBE itself needs a script to run. Strip every existing <script> block, so
    # the only executable left is the probe's.
    src = re.sub(r"(?is)<script\b.*?</script>", "", src)
    script = PROBE_TMPL % selector
    with open(out_html, "w") as f:
        f.write(_append_probe(src, script))


def height_probe(page, out_html):
    import re
    with open(page) as f:
        src = f.read()
    src = re.sub(r"(?is)<script\b.*?</script>", "", src)
    # The height is carried on a synthetic #__ffh div appended at load, then read by
    # the SAME rect probe the geometry harness uses (a div's getBoundingClientRect
    # height is its CSS height here, so the canvas bit-grid machinery is reused and
    # trusted). The probe runs on load and replaces the body AFTER measuring.
    with open(out_html, "w") as f:
        f.write(_append_probe(src, HEIGHT_SCRIPT + PROBE_TMPL % "#__ffh"))


def height(path):
    """Decodes the scrollHeight carried by the #__ffh sentinel: the probe encodes
    one rect (its height), which decode() returns as the first element's h value."""
    vals = decode(path)
    if not vals:
        raise ValueError("%s: height probe produced no rect" % path)
    return vals[0][3]


def main(argv):
    if len(argv) < 2:
        print(__doc__)
        return 1
    if argv[1] == "probe":
        if len(argv) != 5:
            print("usage: ffgeom probe <page.html> <selector> <out.html>")
            return 1
        probe(argv[2], argv[3], argv[4])
        return 0
    if argv[1] == "height-probe":
        if len(argv) != 4:
            print("usage: ffgeom height-probe <page.html> <out.html>")
            return 1
        height_probe(argv[2], argv[3])
        return 0
    if argv[1] == "height":
        if len(argv) != 3:
            print("usage: ffgeom height <screenshot.png>")
            return 1
        try:
            print(height(argv[2]))
        except ValueError as e:
            print("ffgeom: %s" % e, file=sys.stderr)
            return 1
        return 0
    if argv[1] == "decode":
        if len(argv) != 3:
            print("usage: ffgeom decode <screenshot.png>")
            return 1
        try:
            vals = decode(argv[2])
        except ValueError as e:
            print("ffgeom: %s" % e, file=sys.stderr)
            return 1
        for i, v in enumerate(vals):
            print("elem%d top=%d left=%d w=%d h=%d ml=%d mr=%d pl=%d pr=%d"
                  % (i, v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7]))
        return 0
    print(__doc__)
    return 1


if __name__ == "__main__":
    sys.exit(main(sys.argv))
