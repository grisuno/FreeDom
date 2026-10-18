#!/usr/bin/env python3
"""
ffq -- ask Firefox what it computed, as TEXT.

`make geom` prints Firefox's rects as an image; this tool prints them (and any computed
property) as plain lines, so a layout difference is one grep away instead of a guess.
The page loads with JavaScript OFF and the network dead, exactly like `make parity`
(file:// stays reachable); the query itself runs through geckodriver, which executes
outside the page's own script policy.

Usage: ffq.py <page.html> <css-selector> [prop ...] [--width N] [--height N] [--max N]
  Prints one line per match:
    <i> <tag>.<class> x=.. y=.. w=.. h=..  prop=value ...
  Coordinates are document coordinates (scroll included), integers.
"""

import os
import shutil
import sys


def main():
    args = sys.argv[1:]
    width, height, mx = 1000, 1080, 40
    props = []
    pos = []
    i = 0
    while i < len(args):
        a = args[i]
        if a == "--width":
            width = int(args[i + 1]); i += 2
        elif a == "--height":
            height = int(args[i + 1]); i += 2
        elif a == "--max":
            mx = int(args[i + 1]); i += 2
        else:
            pos.append(a); i += 1
    if len(pos) < 2:
        print(__doc__, file=sys.stderr)
        return 1
    page = os.path.abspath(pos[0])
    sel = pos[1]
    props = pos[2:]
    from selenium import webdriver
    from selenium.webdriver.firefox.options import Options
    from selenium.webdriver.firefox.service import Service

    opts = Options()
    opts.add_argument("-headless")
    opts.set_preference("javascript.enabled", False)
    opts.set_preference("widget.gtk.overlay-scrollbars.enabled", True)
    opts.set_preference("ui.useOverlayScrollbars", 1)
    opts.set_preference("network.proxy.type", 1)
    opts.set_preference("network.proxy.http", "127.0.0.1")
    opts.set_preference("network.proxy.http_port", 1)
    opts.set_preference("network.proxy.ssl", "127.0.0.1")
    opts.set_preference("network.proxy.ssl_port", 1)
    opts.set_preference("network.proxy.allow_hijacking_localhost", True)
    drv = None
    try:
        drv = webdriver.Firefox(
            options=opts,
            service=Service(executable_path=shutil.which("geckodriver"), log_output=os.devnull))
        drv.get("file://" + page)
        drv.set_window_size(width, height)
        iw, ih = drv.execute_script("return [innerWidth, innerHeight]")
        drv.set_window_size(width + (width - iw), height + (height - ih))
        script = """
        var sel = arguments[0], props = arguments[1], mx = arguments[2];
        var out = [];
        var els = document.querySelectorAll(sel);
        for (var i = 0; i < els.length && i < mx; ++i) {
          var e = els[i], r = e.getBoundingClientRect(), cs = getComputedStyle(e);
          var line = i + " " + e.tagName.toLowerCase() +
            (e.className && typeof e.className === 'string' ? "." + e.className.trim().split(/\\s+/).join(".") : "") +
            " x=" + Math.round(r.left + scrollX) + " y=" + Math.round(r.top + scrollY) +
            " w=" + Math.round(r.width) + " h=" + Math.round(r.height);
          for (var k = 0; k < props.length; ++k) line += "  " + props[k] + "=" + cs.getPropertyValue(props[k]);
          out.push(line);
        }
        out.push("matches=" + els.length);
        return out;
        """
        for line in drv.execute_script(script, sel, props, mx):
            print(line)
    finally:
        if drv is not None:
            try:
                drv.quit()
            except Exception:  # noqa: BLE001
                pass
    return 0


if __name__ == "__main__":
    sys.exit(main())
