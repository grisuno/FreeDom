#!/usr/bin/env python3
"""
guishot -- a picture of the REAL Freedom window for the README.

The window runs in a nested weston (Xvfb + weston, pixman renderer: the same display
harness as guitime/guiscroll). The first URL is opened on the command line; every other
one in a new tab (xdotool: Ctrl+T, type, Enter), then the first tab is brought back to the
front, so the picture shows the tab strip, the omnibox and the connection badge of a real
session. FREEDOM_GUI_SHOT writes what the window's own painter drew (client-side
decorations included), so nothing of the virtual desktop leaks into the image.

The session is throwaway: HOME and FREEDOM_HOSTS_DIR point at a temporary copy of the
repository's config/, so the operator's profile, bookmarks and host lists are never read
or written (the auto-allow of CDN hosts writes to allow.conf). A page pictured with its
author CSS must be in the repository's allow.conf and js.conf (the trusted-host doctrine).

Usage: guishot.py [--bin PATH] [--out PNG] [--wait S] URL [URL...]
Exit 0 when the picture was written, 1 when it was not, 2 when the environment is missing.
"""

import argparse
import os
import shutil
import subprocess
import sys
import tempfile
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import guitime  # noqa: E402  (start_display: one display harness for every GUI measurement)

TAB_GAP_S = 2.5
KEY_DELAY_MS = 20
SHOT_PERIOD_S = 3.5
POINTER_PARK = ("1290", "890")


def xdo(env, *args):
    subprocess.run(["xdotool", *args], env=env, check=False,
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--bin", default="build/freedom")
    ap.add_argument("--out", default="docs/img/freedom-ui.png")
    ap.add_argument("--wait", type=float, default=12.0, help="seconds for the first page to load")
    ap.add_argument("urls", nargs="+")
    a = ap.parse_args()
    if shutil.which("xdotool") is None:
        print("guishot: xdotool not found", file=sys.stderr)
        return 2
    tmp = tempfile.mkdtemp(prefix="guishot-")
    procs = ()
    proc = None
    try:
        started = guitime.start_display(tmp)
        if started is None:
            return 2
        env, procs = started
        hosts = os.path.join(tmp, "hosts")
        shutil.copytree("config", hosts)
        home = os.path.join(tmp, "home")
        os.mkdir(home)
        shot = os.path.join(tmp, "shot.png")
        renv = dict(env, HOME=home, FREEDOM_HOSTS_DIR=hosts, FREEDOM_GUI_SHOT=shot)
        xenv = dict(os.environ, DISPLAY=env["DISPLAY"])
        proc = subprocess.Popen([a.bin, a.urls[0]], env=renv,
                                stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        time.sleep(a.wait)
        xdo(xenv, "mousemove", "650", "450")
        for url in a.urls[1:]:
            xdo(xenv, "key", "ctrl+t")
            time.sleep(0.6)
            xdo(xenv, "type", "--delay", str(KEY_DELAY_MS), url)
            xdo(xenv, "key", "Return")
            time.sleep(TAB_GAP_S)
        xdo(xenv, "key", "ctrl+1")
        xdo(xenv, "mousemove", *POINTER_PARK)
        time.sleep(a.wait / 2)
        # The painter writes at most one shot every 3 s: one scroll notch down and back up
        # forces two fresh frames of the settled first tab.
        xdo(xenv, "mousemove", "650", "450")
        xdo(xenv, "click", "5")
        time.sleep(SHOT_PERIOD_S)
        xdo(xenv, "key", "Home")
        xdo(xenv, "mousemove", *POINTER_PARK)
        time.sleep(SHOT_PERIOD_S)
        xdo(xenv, "mousemove", *POINTER_PARK)
        time.sleep(1.0)
        if proc.poll() is not None:
            print("guishot: the window exited (status %d)" % proc.returncode, file=sys.stderr)
            return 1
        if not os.path.exists(shot):
            print("guishot: the window never painted a document", file=sys.stderr)
            return 1
        os.makedirs(os.path.dirname(os.path.abspath(a.out)), exist_ok=True)
        shutil.copyfile(shot, a.out)
        print("guishot: wrote %s" % a.out)
        return 0
    finally:
        if proc is not None and proc.poll() is None:
            proc.kill()
            proc.wait()
        for p in procs:
            p.kill()
            p.wait()
        shutil.rmtree(tmp, ignore_errors=True)


if __name__ == "__main__":
    sys.exit(main())
