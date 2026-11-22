#!/usr/bin/env python3
"""
guiscroll -- what one frame costs in the REAL Freedom window while the user scrolls.

guitime measures "navigate -> painted and idle"; this measures the frames AFTER that: the
page is loaded in a nested weston (Xvfb + weston, pixman renderer, same harness as guitime),
then xdotool turns the mouse wheel over the content N times, one notch every WHEEL_GAP_S.
The window runs with FREEDOM_JS_PROFILE=1, so every frame prints its phases on stderr
("gui-profile paint(total) ..." and the layout_doc / position_doc lines). Only the frames
painted after the first wheel notch are counted.

Usage: guiscroll.py [--bin PATH] [--notches N] <page.html> ...
Prints one line per page:  <name>\t<frames>\t<median frame ms>\t<p90 frame ms>\t<median layout ms>
Exit 0 when every page was measured, 1 on a failed measurement, 2 when the environment is missing.
"""

import os
import shutil
import statistics
import subprocess
import sys
import tempfile
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import guitime  # noqa: E402  (start_display: one display harness for every GUI measurement)

LOAD_WAIT_S = 6.0
WHEEL_GAP_S = 0.08
SETTLE_S = 1.5
MARK = "guiscroll-start"


def phase_ms(line, phase):
    parts = line.split()
    if len(parts) >= 4 and parts[0] == "gui-profile" and parts[1] == phase:
        try:
            return float(parts[2])
        except ValueError:
            return None
    return None


def one_page(binary, page, env, prof, tmp, notches):
    errpath = os.path.join(tmp, "err.txt")
    renv = dict(env, FREEDOM_AS_HOST="corpus.test", FREEDOM_JS="off", FREEDOM_HOSTS_DIR=prof,
                FREEDOM_JS_PROFILE="1")
    with open(errpath, "w") as errf:
        proc = subprocess.Popen([binary, page], env=renv, stdout=subprocess.DEVNULL, stderr=errf)
        try:
            time.sleep(LOAD_WAIT_S)
            xenv = dict(os.environ, DISPLAY=env["DISPLAY"])
            subprocess.run(["xdotool", "mousemove", "650", "550"], env=xenv, check=False)
            errf.flush()
            mark = os.path.getsize(errpath)
            for _ in range(notches):
                subprocess.run(["xdotool", "click", "5"], env=xenv, check=False)
                time.sleep(WHEEL_GAP_S)
            time.sleep(SETTLE_S)
        finally:
            proc.kill()
            proc.wait()
    with open(errpath, errors="replace") as fh:
        fh.seek(mark)
        lines = fh.read().splitlines()
    for l in lines:
        if "stale hit" in l:
            print("guiscroll: %s" % l.strip(), file=sys.stderr)
    frames = [v for v in (phase_ms(l, "paint(total)") for l in lines) if v is not None]
    layouts = [v for v in (phase_ms(l, "layout_doc") for l in lines) if v is not None]
    if os.environ.get("GUISCROLL_PHASES"):
        phases = {}
        for l in lines:
            parts = l.split()
            if len(parts) >= 3 and parts[0] == "gui-profile":
                try:
                    phases.setdefault(parts[1], []).append(float(parts[2]))
                except ValueError:
                    pass
        for k, v in sorted(phases.items()):
            print("  %-18s n=%-4d median %.1f ms" % (k, len(v), statistics.median(v)))
    return frames, layouts


def main():
    args = sys.argv[1:]
    binary, notches, hosts, pages = "./build/freedom", 20, "tests/parity/hosts", []
    i = 0
    while i < len(args):
        if args[i] == "--bin":
            binary = args[i + 1]; i += 2
        elif args[i] == "--notches":
            notches = int(args[i + 1]); i += 2
        else:
            pages.append(args[i]); i += 1
    if not pages:
        print(__doc__.strip().splitlines()[-3], file=sys.stderr)
        return 1
    if not os.access(binary, os.X_OK) or shutil.which("xdotool") is None:
        print("guiscroll: needs %s built and xdotool installed" % binary, file=sys.stderr)
        return 2
    with tempfile.TemporaryDirectory(prefix="guiscroll-") as tmp:
        prof = os.path.join(tmp, "profile")
        shutil.copytree(hosts, prof)
        disp = guitime.start_display(tmp)
        if disp is None:
            return 2
        env, procs = disp
        env = dict(env, DISPLAY=procs_display(procs))
        rc = 0
        try:
            for page in pages:
                name = os.path.basename(page)
                name = name[:-5] if name.endswith(".html") else name
                frames, layouts = one_page(os.path.abspath(binary), os.path.abspath(page), env,
                                           prof, tmp, notches)
                if not frames:
                    print("guiscroll: %s: no frame was painted while scrolling" % name, file=sys.stderr)
                    rc = 1
                    continue
                frames.sort()
                p90 = frames[min(len(frames) - 1, int(len(frames) * 0.9))]
                lay = statistics.median(layouts) if layouts else 0.0
                print("%s\t%d\t%.1f\t%.1f\t%.1f\t(%d layouts)" % (name, len(frames),
                      statistics.median(frames), p90, lay, len(layouts)))
                sys.stdout.flush()
        finally:
            for p in procs:
                p.kill()
                p.wait()
        return rc


def procs_display(procs):
    """The X display guitime.start_display put Xvfb on (it is the second process's argv)."""
    xv = procs[1]
    return xv.args[1]


if __name__ == "__main__":
    sys.exit(main())
