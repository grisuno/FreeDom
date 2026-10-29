#!/usr/bin/env python3
"""
guitime -- how long the REAL Freedom window takes from "navigate" to "painted and idle".

Not headless: the browser is the GUI binary running in a nested weston (Xvfb + weston, pixman
renderer), loading the page through the same do_load/render/paint path a user's session takes.
The only addition is FREEDOM_GUI_TIMING=<file>: once the page is loaded, no background job or JS tick
is pending and no new frame was painted for 150 ms, the window writes {"ms": <last paint - navigation
request>} and exits (FREEDOM_GUI_EXIT_AT_IDLE). Nothing is timed in a separate mode (spec/parity.md).

The page is measured under the corpus policy (FREEDOM_AS_HOST=corpus.test with tests/parity/hosts:
presentation trust, JavaScript off), the same one `make parity` and tools/fftime.py use. A scratch
profile directory keeps the user's own preferences out of the measurement. If Xvfb or weston is
missing the tool says so and exits 2: it never falls back to a different, headless measurement.

Usage: guitime.py [--runs N] [--bin PATH] [--hosts DIR] <page.html> ...
Prints one line per page:  <name>\t<median ms>\t<min>\t<max>
Exit 0 when every page was measured, 1 on a failed measurement, 2 when the environment is missing.
"""

import json
import os
import shutil
import statistics
import subprocess
import sys
import tempfile
import time

PER_RUN_TIMEOUT_S = 90
START_ATTEMPTS = 20


def start_display(workdir):
    """Starts Xvfb and a nested weston; returns (env, processes) or None when unavailable."""
    for tool in ("Xvfb", "weston"):
        if shutil.which(tool) is None:
            print("guitime: %s not found: the GUI cannot be measured here" % tool, file=sys.stderr)
            return None
    num = 90 + os.getpid() % 9
    disp = ":%d" % num
    socket_name = "wl-guitime-%d" % os.getpid()
    runtime = os.environ.get("XDG_RUNTIME_DIR", "/run/user/%d" % os.getuid())
    xv = subprocess.Popen(["Xvfb", disp, "-screen", "0", "1600x1100x24"],
                          stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    time.sleep(1.0)
    wenv = dict(os.environ, DISPLAY=disp)
    ws = subprocess.Popen(["weston", "--backend=x11-backend.so", "--renderer=pixman", "--width=1300",
                           "--height=900", "--socket=" + socket_name, "--no-config"],
                          env=wenv, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    sock = os.path.join(runtime, socket_name)
    for _ in range(START_ATTEMPTS):
        if os.path.exists(sock):
            break
        time.sleep(0.5)
    else:
        for p in (ws, xv):
            p.kill()
        print("guitime: weston did not come up", file=sys.stderr)
        return None
    env = dict(os.environ, WAYLAND_DISPLAY=socket_name, XDG_RUNTIME_DIR=runtime)
    return env, (ws, xv)


def one_run(binary, page, env, hosts_dir, tmp):
    out = os.path.join(tmp, "t.json")
    if os.path.exists(out):
        os.unlink(out)
    renv = dict(env, FREEDOM_GUI_TIMING=out, FREEDOM_GUI_EXIT_AT_IDLE="1",
                FREEDOM_AS_HOST="corpus.test", FREEDOM_JS="off", FREEDOM_HOSTS_DIR=hosts_dir)
    # GUITIME_STDERR=file keeps the window's stderr (FREEDOM_JS_PROFILE stage lines) for the last run.
    errpath = os.environ.get("GUITIME_STDERR")
    errf = open(errpath, "w") if errpath else subprocess.DEVNULL
    proc = subprocess.Popen([binary, page], env=renv, stdout=subprocess.DEVNULL, stderr=errf)
    deadline = time.time() + PER_RUN_TIMEOUT_S
    try:
        while time.time() < deadline:
            if os.path.exists(out) and proc.poll() is not None:
                break
            if proc.poll() is not None:
                break
            time.sleep(0.05)
    finally:
        if proc.poll() is None:
            proc.kill()
        proc.wait()
    try:
        with open(out) as fh:
            return float(json.load(fh)["ms"])
    except (OSError, ValueError, KeyError):
        return None


def main():
    args = sys.argv[1:]
    runs, binary, hosts, pages = 3, "./build/freedom", "tests/parity/hosts", []
    i = 0
    while i < len(args):
        if args[i] == "--runs":
            runs = int(args[i + 1]); i += 2
        elif args[i] == "--bin":
            binary = args[i + 1]; i += 2
        elif args[i] == "--hosts":
            hosts = args[i + 1]; i += 2
        else:
            pages.append(args[i]); i += 1
    if not pages:
        print("usage: guitime.py [--runs N] <page.html> ...", file=sys.stderr)
        return 1
    if not os.access(binary, os.X_OK):
        print("guitime: %s is not built" % binary, file=sys.stderr)
        return 1
    with tempfile.TemporaryDirectory(prefix="guitime-") as tmp:
        prof = os.path.join(tmp, "profile")          # scratch profile: prefs/cache never touch the repo
        shutil.copytree(hosts, prof)
        disp = start_display(tmp)
        if disp is None:
            return 2
        env, procs = disp
        rc = 0
        try:
            first = True
            for page in pages:
                path = os.path.abspath(page)
                name = os.path.basename(page)
                name = name[:-5] if name.endswith(".html") else name
                if first:                             # one untimed run: font/config caches, like a returning user
                    one_run(os.path.abspath(binary), path, env, prof, tmp)
                    first = False
                samples = []
                for _ in range(runs):
                    ms = one_run(os.path.abspath(binary), path, env, prof, tmp)
                    if ms is not None:
                        samples.append(ms)
                if not samples:
                    print("guitime: %s: no timing was produced" % name, file=sys.stderr)
                    rc = 1
                    continue
                print("%s\t%.0f\t%.0f\t%.0f" % (name, statistics.median(samples), min(samples), max(samples)))
                sys.stdout.flush()
        finally:
            for p in procs:
                p.kill()
                p.wait()
        return rc


if __name__ == "__main__":
    sys.exit(main())
