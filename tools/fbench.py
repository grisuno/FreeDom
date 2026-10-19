#!/usr/bin/env python3
"""
fbench -- turn the PNG pairs `make parity` leaves behind into something you can act on.

`make parity` prints one score per page. To fix a page you then need to SEE where the two
engines part ways. This reads build/parity/<name>.fd.png (Freedom) and <name>.ff.png
(Firefox) and, per page:
  * writes build/bench/<name>.sbs.png: Freedom | Firefox side by side, cropped to the
    band you ask for, so one Read shows the difference;
  * prints the first row where the pictures diverge and the worst 100 px bands by mean
    luminance difference, so you know which y to crop next;
  * ranks the pages by score and shows the delta against tests/parity/baseline.tsv.

Every page the README shows (README_PAGES) is also republished: its docs/img/compare-*.png
is rewritten from the fresh pair and its score in the README table is updated, so the
README always carries the latest render. --no-readme skips that.

Usage: fbench.py [--from Y] [--rows N] [--band PX] [--no-readme] [page ...]
  no page  -> every page that has a PNG pair
Run `make fbench PAGES="a b" FROM=1000 ROWS=800` to refresh the pair first.
"""

import os
import sys

import numpy as np
from PIL import Image, ImageDraw

PARITY = "build/parity"
# parity page -> (docs/img file, README label the score follows)
README_PAGES = {
    "hackernews": ("compare-hackernews.png", "Hacker News"),
    "wikipedia": ("compare-wikipedia.png", "Wikipedia"),
    "site-andreagrandi": ("compare-site-andreagrandi.png", "andreagrandi.it"),
    "huggingface": ("compare-huggingface.png", "Hugging Face"),
    "site-github": ("compare-site-github.png", "GitHub"),
    "slashdot": ("compare-slashdot.png", "Slashdot"),
    "lobsters": ("compare-lobsters.png", "lobste.rs"),
    "site-discord": ("compare-site-discord.png", "Discord"),
    "site-gitlab": ("compare-site-gitlab.png", "GitLab"),
}
README_ROWS = 1100
OUT = "build/bench"


def load_baseline():
    base = {}
    try:
        with open("tests/parity/baseline.tsv") as fh:
            for line in fh:
                k, _, v = line.partition("\t")
                if v.strip():
                    base[k] = float(v)
    except OSError:
        pass
    return base


def load_current():
    cur = {}
    try:
        with open(PARITY + "/current.tsv") as fh:
            for line in fh:
                k, _, v = line.partition("\t")
                if v.strip():
                    cur[k] = float(v)
    except OSError:
        pass
    return cur


def luma(img):
    return np.asarray(img.convert("L"), dtype=np.float32)


def bands(fd, ff, band):
    h = min(fd.shape[0], ff.shape[0])
    w = min(fd.shape[1], ff.shape[1])
    rows = np.abs(fd[:h, :w] - ff[:h, :w]).mean(axis=1)
    first = next((i for i, v in enumerate(rows) if v > 2.0), None)
    scored = []
    for y in range(0, h, band):
        scored.append((float(rows[y:y + band].mean()), y))
    scored.sort(reverse=True)
    return first, scored[:3]


def sbs(name, start, nrows):
    a = Image.open("%s/%s.fd.png" % (PARITY, name)).convert("RGB")
    b = Image.open("%s/%s.ff.png" % (PARITY, name)).convert("RGB")
    end = start + nrows
    a = a.crop((0, start, a.width, min(end, max(a.height, start + 1))))
    b = b.crop((0, start, b.width, min(end, max(b.height, start + 1))))
    h = max(a.height, b.height)
    canvas = Image.new("RGB", (a.width + b.width + 8, h + 16), (255, 0, 255))
    canvas.paste(a, (0, 16))
    canvas.paste(b, (a.width + 8, 16))
    d = ImageDraw.Draw(canvas)
    d.text((4, 2), "Freedom  y=%d" % start, fill=(255, 255, 255))
    d.text((a.width + 12, 2), "Firefox", fill=(255, 255, 255))
    os.makedirs(OUT, exist_ok=True)
    path = "%s/%s.sbs.png" % (OUT, name)
    canvas.save(path)
    return path


def publish_readme(name, score):
    """Rewrite the README picture of `name` and the score printed beside its label."""
    import re
    img, label = README_PAGES[name]
    path = sbs(name, 0, README_ROWS)
    os.makedirs("docs/img", exist_ok=True)
    Image.open(path).save("docs/img/" + img, optimize=True)
    if score == score:
        try:
            with open("README.md", encoding="utf8") as fh:
                text = fh.read()
            new = re.sub(r"(\b%s) \(\d+(?:\.\d+)?\)" % re.escape(label),
                         r"\1 (%.2f)" % score, text, count=1)
            if new != text:
                with open("README.md", "w", encoding="utf8") as fh:
                    fh.write(new)
        except OSError:
            pass


def main():
    args = sys.argv[1:]
    readme = True
    start, nrows, band = 0, 1100, 100
    names = []
    i = 0
    while i < len(args):
        if args[i] == "--from":
            start = int(args[i + 1]); i += 2
        elif args[i] == "--rows":
            nrows = int(args[i + 1]); i += 2
        elif args[i] == "--no-readme":
            readme = False; i += 1
        elif args[i] == "--band":
            band = int(args[i + 1]); i += 2
        else:
            names.append(args[i]); i += 1
    if not names:
        names = sorted(f[:-7] for f in os.listdir(PARITY) if f.endswith(".fd.png")
                       and os.path.exists("%s/%s.ff.png" % (PARITY, f[:-7])))
    base, cur = load_baseline(), load_current()
    rows = []
    for n in names:
        try:
            fd = luma(Image.open("%s/%s.fd.png" % (PARITY, n)))
            ff = luma(Image.open("%s/%s.ff.png" % (PARITY, n)))
        except OSError:
            print("%s: no PNG pair (run make fbench PAGES=%s)" % (n, n))
            continue
        first, worst = bands(fd, ff, band)
        path = sbs(n, start, nrows)
        if readme and n in README_PAGES:
            publish_readme(n, cur.get(n, float("nan")))
        rows.append((cur.get(n, float("nan")), n, fd.shape[0], ff.shape[0], first, worst, path))
    rows.sort(key=lambda r: -(r[0] if r[0] == r[0] else -1))
    for score, n, hfd, hff, first, worst, path in rows:
        delta = score - base[n] if n in base and score == score else float("nan")
        print("%-22s score %7.2f (%+.2f vs baseline)  h %d vs %d (x%.2f)" %
              (n, score, delta, hfd, hff, hfd / max(hff, 1)))
        print("    first divergence y=%s   worst %d px bands: %s" %
              (first, band, ", ".join("y=%d (%.1f)" % (y, v) for v, y in worst)))
        print("    %s" % path)
    return 0


if __name__ == "__main__":
    sys.exit(main())
