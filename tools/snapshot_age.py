#!/usr/bin/env python3
"""Report parity snapshots older than N days (stamped by tools/snapshot.py).

Usage: snapshot_age.py PAGES_DIR MAX_DAYS
Exit 0 always: staleness is a warning, a page without a stamp predates the stamp and is
listed as `unstamped` so it can be re-frozen when it next matters.
"""
import datetime
import os
import re
import sys

STAMP = re.compile(rb"<!-- freedom-snapshot url=(\S+) date=(\d{4}-\d{2}-\d{2}) -->")


def main():
    if len(sys.argv) != 3:
        sys.exit("usage: snapshot_age.py PAGES_DIR MAX_DAYS")
    root, limit = sys.argv[1], int(sys.argv[2])
    today = datetime.date.today()
    stale = unstamped = 0
    for name in sorted(os.listdir(root)):
        if not name.endswith(".html"):
            continue
        with open(os.path.join(root, name), "rb") as fh:
            m = STAMP.search(fh.read(512))
        if m is None:
            unstamped += 1
            continue
        age = (today - datetime.date.fromisoformat(m.group(2).decode())).days
        if age > limit:
            stale += 1
            print("stale (%d days): %s <- %s" % (age, name, m.group(1).decode()))
    print("snapshots: %d stale, %d unstamped (predate the stamp)" % (stale, unstamped))


if __name__ == "__main__":
    main()
