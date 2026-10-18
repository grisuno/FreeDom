#!/usr/bin/env python3
"""
prune -- cut a corpus page down to ONE subtree, keeping its whole ancestor chain.

Isolating a layout bug on a 400 KB page by eye is slow; isolating it by deleting
everything that is not on the path to the element is mechanical. The <head> (every
<style> and <link>) is kept as is, so the cascade is untouched; in the <body> only the
target subtree and its ancestors survive, with every other sibling dropped along the
path. Scripts are removed (both engines render with JS off anyway).

Usage: prune.py <page.html> <xpath> <out.html>
  xpath  selects the element(s) to keep, e.g. '//nav[@class="nav-primary"]'
Prints the number of matched elements; exits 1 when none matched.
"""

import sys

from lxml import etree, html


def main():
    if len(sys.argv) != 4:
        print("usage: prune.py <page.html> <xpath> <out.html>", file=sys.stderr)
        return 1
    src, xpath, out = sys.argv[1], sys.argv[2], sys.argv[3]
    with open(src, "rb") as fh:
        doc = html.fromstring(fh.read())
    targets = doc.xpath(xpath)
    if not targets:
        print("prune: no match", file=sys.stderr)
        return 1
    keep = set()
    for t in targets:
        for n in t.iter():
            keep.add(n)
        for a in t.iterancestors():
            keep.add(a)
    body = doc.find("body")
    if body is not None:
        for el in list(body.iter()):
            if el in keep or el is body:
                continue
            par = el.getparent()
            if par is None or par not in keep and par is not body:
                continue
            # Drop the sibling but keep its tail text out of the page as well.
            par.remove(el)
    for s in doc.xpath("//script"):
        if s.getparent() is not None:
            s.getparent().remove(s)
    with open(out, "wb") as fh:
        fh.write(b"<!DOCTYPE html>\n" + etree.tostring(doc, method="html"))
    print(len(targets))
    return 0


if __name__ == "__main__":
    sys.exit(main())
