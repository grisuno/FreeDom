#!/usr/bin/env python3
"""
pngprof -- structural ink-profile dump for page screenshots.

Build-time tool for Freedom layout work (companion to tools/pngdiff.c). Where
pngdiff reduces two renders to one scalar score, pngprof prints WHERE the ink
sits: the horizontal column profile split into vertical bands, and the
cumulative vertical ink distribution. That is what turns a divergence like
"slashdot col_mae 0.39" into a statement like "the article column spans
x=120..600 in Firefox but x=0..950 in Freedom".

It answers the questions an agent cannot answer by looking at the PNG: with no
image input available (or when the numbers matter more than the picture), the
agent reads these profiles instead. Ink is defined against the image's modal
background luminance, exactly like pngdiff, so a dark author theme and a forced
light theme compare meaningfully.

Decoder: pure python (zlib + the five PNG filters), no third-party packages, so
it runs anywhere the repo runs. RGBA/RGB/grey/16-bit screenshots all normalise
to an 8-bit RGB row buffer. It reads only local files that the harness or the
operator just produced; it never sees remote content and is not part of the
browser's attack surface.

Usage:
  pngprof <image.png> [--bands N] [--cols C] [--rows R]

Output (stdout):
  - image width/height and the background luminance used
  - the column profile: C buckets, each printed as the ink fraction of that
    bucket's cells, repeated per vertical band
  - the cumulative vertical ink distribution over R bands (0..1)

No emojis, no network, deterministic.
"""

import sys
import zlib
import struct


def load_rows(path):
    data = open(path, "rb").read()
    if data[:8] != b"\x89PNG\r\n\x1a\n":
        raise ValueError("%s: not a PNG" % path)
    pos = 8
    idat = b""
    width = height = bit_depth = color_type = None
    while pos < len(data):
        length = struct.unpack(">I", data[pos:pos + 4])[0]
        typ = data[pos + 4:pos + 8]
        if typ == b"IHDR":
            width, height, bit_depth, color_type = struct.unpack(
                ">IIBB", data[pos + 8:pos + 18])
        elif typ == b"IDAT":
            idat += data[pos + 8:pos + 8 + length]
        elif typ == b"IEND":
            break
        pos += 12 + length
    if width is None or height is None:
        raise ValueError("%s: no IHDR" % path)
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


def render_glyph(v):
    if v > 0.5:
        return "#"
    if v > 0.2:
        return "+"
    if v > 0.05:
        return "."
    return " "


def main(argv):
    if len(argv) < 2:
        print(__doc__)
        return 1
    nbands = 3
    ncols = 100
    nrows = 40
    i = 2
    while i < len(argv):
        if argv[i] == "--bands" and i + 1 < len(argv):
            nbands = max(1, int(argv[i + 1]))
            i += 2
        elif argv[i] == "--cols" and i + 1 < len(argv):
            ncols = max(1, int(argv[i + 1]))
            i += 2
        elif argv[i] == "--rows" and i + 1 < len(argv):
            nrows = max(1, int(argv[i + 1]))
            i += 2
        else:
            i += 1
    width, height, channels, rows = load_rows(argv[1])

    hist = [0] * 256
    for r in rows:
        for i in range(0, len(r), channels):
            hist[int(lum(r[i:i + 3]) + 0.5)] += 1
    bg = hist.index(max(hist))

    colh = [[0] * ncols for _ in range(nbands)]
    rowink = [0] * nrows
    total = 0
    for y, r in enumerate(rows):
        rb = y * nrows // height
        yb = min(nbands - 1, y * nbands // height)
        for i in range(0, len(r), channels):
            if abs(lum(r[i:i + 3]) - bg) > 24:
                colh[yb][(i // channels) * ncols // width] += 1
                rowink[rb] += 1
                total += 1

    print("width %d height %d bg %d" % (width, height, bg))
    band_cells = (width / ncols) * height / nbands
    for yb in range(nbands):
        band = [c / band_cells for c in colh[yb]]
        glyphs = ""
        for i in range(0, ncols, 2):
            glyphs += render_glyph(max(band[i], band[i + 1]))
        print("band %d..%d%% %s" % (yb * 100 // nbands,
                                    (yb + 1) * 100 // nbands, glyphs))
    if total > 0:
        acc = 0
        print("cumulative vertical ink:")
        for j in range(nrows):
            acc += rowink[j]
            print("  y %3d%% %.2f" % (j * 100 // nrows, acc / total))
    else:
        print("cumulative vertical ink: (no ink found)")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
