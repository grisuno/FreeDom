#!/usr/bin/env python3
"""
ffshot -- full-page Firefox screenshot at a FIXED viewport, for `make parity`/`make wpt`.

`firefox --screenshot` sizes its viewport itself, so a page whose layout depends on `vh`
(a hero of `min-height:100vh`, a sticky sidebar capped at `100vh`) rendered against a
different viewport than Freedom's normalised 1080px one and scored as an engine bug.
This drives the same Firefox through geckodriver with an explicit window size and asks for
the full-page capture, so both engines see the same `vh`.

Same policy as the rest of the harness: JavaScript off and every network request sent to a
dead proxy (file:// and data: stay reachable), because Freedom renders with JS off and
blocks third parties by doctrine -- the reference has to measure the same document.

Usage: ffshot.py <page.html> <out.png> [width] [height]
Exit 0 on success; any failure prints one line to stderr and exits 1.
"""

import os
import shutil
import sys


def main():
    if len(sys.argv) < 3:
        print("usage: ffshot.py <page.html> <out.png> [width] [height]", file=sys.stderr)
        return 1
    page = os.path.abspath(sys.argv[1])
    out = os.path.abspath(sys.argv[2])
    width = int(sys.argv[3]) if len(sys.argv) > 3 else 1000
    height = int(sys.argv[4]) if len(sys.argv) > 4 else 1080
    try:
        from selenium import webdriver
        from selenium.webdriver.firefox.options import Options
        from selenium.webdriver.firefox.service import Service
    except ImportError:
        print("ffshot: python selenium is not installed", file=sys.stderr)
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
    try:
        driver_bin = shutil.which("geckodriver")
        if driver_bin is None:
            print("ffshot: geckodriver not found", file=sys.stderr)
            return 1
        drv = webdriver.Firefox(options=opts,
                                service=Service(executable_path=driver_bin,
                                                log_output=os.devnull))
        drv.get("file://" + page)
        # set_window_size sizes the OUTER window (browser chrome included); measure the
        # difference once and correct it so the VIEWPORT is exactly width x height.
        drv.set_window_size(width, height)
        iw, ih = drv.execute_script("return [innerWidth, innerHeight]")
        drv.set_window_size(width + (width - iw), height + (height - ih))
        if os.environ.get("FFSHOT_DEBUG"):
            print(drv.execute_script("return [innerWidth, innerHeight]"), file=sys.stderr)
        drv.get_full_page_screenshot_as_file(out)
    except Exception as exc:  # noqa: BLE001 -- report and fail, never a stack trace
        print("ffshot: %s" % str(exc).splitlines()[0] if str(exc) else "ffshot: failed",
              file=sys.stderr)
        return 1
    finally:
        if drv is not None:
            try:
                drv.quit()
            except Exception:  # noqa: BLE001
                pass
    return 0


if __name__ == "__main__":
    sys.exit(main())
