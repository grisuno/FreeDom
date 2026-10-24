#!/usr/bin/env python3
"""
fftime -- Firefox's time from "navigate" to "painted and idle", for `make fbench`.

Counterpart of the GUI's FREEDOM_GUI_TIMING (spec/parity.md "Timing"): the clock starts when the
navigation is requested; the time is max(load event end, first painted frame) from the browser's
own Performance Timeline (so it carries no WebDriver round trip). It is a LOWER bound of Firefox's
true idle time (it cannot see later repaints such as image decode), which makes the comparison
unfavourable to Freedom, never to Firefox. Same policy as
the rest of the harness (JavaScript off, every network request sent to a dead proxy, file:// and
data: reachable) and the same viewport as ffshot. One browser session serves every page; each page
gets one untimed warm-up navigation (disk cache, font and layout caches, the way a returning user
sees it) and RUNS timed ones; the median is reported.

Usage: fftime.py [--runs N] [--width W] [--height H] <page.html> ...
Prints one line per page:  <name>\t<median ms>\t<min>\t<max>
Exit 0 when every page was measured; 1 on any failure (reported on stderr).
"""

import os
import shutil
import statistics
import sys
import time

# With the page's JavaScript off, WebDriver cannot run ASYNC scripts (timers and requestAnimationFrame
# never fire in the sandbox), only synchronous ones; so the browser's own Performance Timeline is
# read instead: navigation start (0) -> load event end, and the first painted frame.
TIMELINE = ("var n = performance.getEntriesByType('navigation')[0];"
            "var fcp = 0;"
            "performance.getEntriesByType('paint').forEach(function (e) {"
            "  if (e.name === 'first-contentful-paint') fcp = e.startTime;"
            "  else if (e.name === 'first-paint' && !fcp) fcp = e.startTime; });"
            "return [n ? n.loadEventEnd : 0, fcp];")
PAINT_WAIT_S = 3.0


def main():
    args = sys.argv[1:]
    runs, width, height, pages = 5, 1000, 1080, []
    i = 0
    while i < len(args):
        if args[i] == "--runs":
            runs = int(args[i + 1]); i += 2
        elif args[i] == "--width":
            width = int(args[i + 1]); i += 2
        elif args[i] == "--height":
            height = int(args[i + 1]); i += 2
        else:
            pages.append(args[i]); i += 1
    if not pages:
        print("usage: fftime.py [--runs N] <page.html> ...", file=sys.stderr)
        return 1
    try:
        from selenium import webdriver
        from selenium.webdriver.firefox.options import Options
        from selenium.webdriver.firefox.service import Service
    except ImportError:
        print("fftime: python selenium is not installed", file=sys.stderr)
        return 1
    driver_bin = shutil.which("geckodriver")
    if driver_bin is None:
        print("fftime: geckodriver not found", file=sys.stderr)
        return 1
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
    rc = 0
    try:
        drv = webdriver.Firefox(options=opts,
                                service=Service(executable_path=driver_bin, log_output=os.devnull))
        drv.set_script_timeout(60)
        drv.get("about:blank")
        drv.set_window_size(width, height)
        iw, ih = drv.execute_script("return [innerWidth, innerHeight]")
        drv.set_window_size(width + (width - iw), height + (height - ih))
        for page in pages:
            url = "file://" + os.path.abspath(page)
            name = os.path.basename(page)
            name = name[:-5] if name.endswith(".html") else name
            samples = []
            try:
                for n in range(runs + 1):
                    drv.get("about:blank")
                    drv.get(url)
                    load, fcp = drv.execute_script(TIMELINE)
                    deadline = time.perf_counter() + PAINT_WAIT_S
                    while not fcp and time.perf_counter() < deadline:    # paint entry lands after load
                        time.sleep(0.02)
                        load, fcp = drv.execute_script(TIMELINE)
                    dt = max(load, fcp)
                    if n > 0:                       # run 0 is the warm-up
                        samples.append(dt)
            except Exception as exc:  # noqa: BLE001
                print("fftime: %s: %s" % (name, str(exc).splitlines()[0] if str(exc) else "failed"),
                      file=sys.stderr)
                rc = 1
                continue
            print("%s\t%.0f\t%.0f\t%.0f" % (name, statistics.median(samples), min(samples), max(samples)))
            sys.stdout.flush()
    except Exception as exc:  # noqa: BLE001
        print("fftime: %s" % (str(exc).splitlines()[0] if str(exc) else "failed"), file=sys.stderr)
        rc = 1
    finally:
        if drv is not None:
            try:
                drv.quit()
            except Exception:  # noqa: BLE001
                pass
    return rc


if __name__ == "__main__":
    sys.exit(main())
