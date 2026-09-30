#!/usr/bin/env python3
"""Freeze a live page into one self-contained HTML file for `make parity`.

Both engines must render the SAME document offline (spec/parity.md), so every
same-site <link rel=stylesheet> is fetched once and inlined as <style>, and
scripts are dropped: parity runs JS off on both sides. Nothing else is fetched.
"""
import re
import sys
import urllib.parse
import urllib.request

UA = "Mozilla/5.0 (X11; Linux x86_64; rv:128.0) Gecko/20100101 Firefox/128.0"
MAX_BYTES = 8 * 1024 * 1024


def fetch(url):
    req = urllib.request.Request(url, headers={"User-Agent": UA})
    with urllib.request.urlopen(req, timeout=30) as r:
        data = r.read(MAX_BYTES)
        cs = r.headers.get_content_charset() or "utf-8"
    return data.decode(cs, errors="replace")


IMPORT_RE = re.compile(
    r'@import\s+(?:url\(\s*["\']?([^"\')]+)["\']?\s*\)|["\']([^"\']+)["\'])\s*([^;]*);',
    re.I)
MAX_IMPORT_DEPTH = 4


def expand_imports(css, base, depth):
    """Replace each @import with the imported text (wrapped in @media when the
    import carries a media condition), resolved against the SHEET url."""
    def repl(m):
        if depth >= MAX_IMPORT_DEPTH:
            return ""
        url = urllib.parse.urljoin(base, m.group(1) or m.group(2))
        cond = m.group(3).strip()
        try:
            text = expand_imports(fetch(url), url, depth + 1)
        except Exception as e:
            sys.stderr.write("skip import %s: %s\n" % (url, e))
            return ""
        return "@media %s {\n%s\n}" % (cond, text) if cond else text
    return IMPORT_RE.sub(repl, css)


def inline_css(html, base):
    def repl(m):
        tag = m.group(0)
        if not re.search(r'rel\s*=\s*["\']?stylesheet', tag, re.I):
            return tag
        href = re.search(r'(?<![\w-])href\s*=\s*["\']([^"\']+)', tag, re.I)
        if not href:
            return tag
        url = urllib.parse.urljoin(base, href.group(1).replace("&amp;", "&"))
        media = re.search(r'media\s*=\s*["\']([^"\']+)', tag, re.I)
        try:
            css = fetch(url)
        except Exception as e:
            sys.stderr.write("skip %s: %s\n" % (url, e))
            return ""
        css = expand_imports(css, url, 0)
        attr = ' media="%s"' % media.group(1) if media else ""
        return "<style%s>\n%s\n</style>" % (attr, css)
    return re.sub(r'<link\b[^>]*>', repl, html, flags=re.I)


def main():
    if len(sys.argv) != 3:
        sys.exit("usage: snapshot.py URL OUT.html")
    url, out = sys.argv[1], sys.argv[2]
    html = fetch(url)
    html = re.sub(r'<script\b[^>]*>.*?</script>', '', html, flags=re.I | re.S)
    html = inline_css(html, url)
    with open(out, "w", encoding="utf-8") as f:
        f.write(html)


if __name__ == "__main__":
    main()
