#!/usr/bin/env python3
"""
mutate -- compile-time mutation testing for the CMocka suites.

One mutant = one operator substitution in one src/ file that has a matching
tests/test_<module>.c. The mutated source replaces the original for a single
`make build/test_<module>` build and run, then the original is restored.

    killed          the suite ran and at least one test failed
    survived        the suite passed on the mutated code (a blind spot)
    killed-by-build the mutation broke -Werror or the link (reported apart,
                    because a syntax error is not the suite's work)

Exit status: 0 when every mutant died, 1 when any mutant survived.

The mutation set is deliberately mechanical (comparison/relational/logical/
arithmetic operators): each is one token swap on a line of the module's own
code, never inside comments or strings. Only the first MUTATE_MAX sites per
file are taken, in line order, so the run stays bounded.

Usage:
    tools/mutate.py [--max N] [--mods a,b,c] [--verbose]
"""
import os
import re
import shutil
import subprocess
import sys

OPS = (
    ("<=", "<"), ("<", "<="), (">=", ">"), (">", ">="),
    ("==", "!="), ("!=", "=="), ("&&", "||"), ("||", "&&"),
    ("+", "-"), ("-", "+"),
)

SKIP_EXTRA_OPS = frozenset(("++", "--", "+=", "-=", "->", "->"))

MUTATE_MAX = int(os.environ.get("MUTATE_MAX", "12"))


def line_sites(text):
    lines = text.split("\n")
    out = []
    in_block = False
    for i, line in enumerate(lines):
        stripped = line.strip()
        if stripped.startswith("#"):
            continue
        if stripped.startswith("//") or stripped.startswith("/*"):
            if stripped.startswith("/*") and "*/" not in stripped:
                in_block = True
            continue
        if in_block:
            if "*/" in line:
                in_block = False
            continue
        if stripped.startswith('"') or stripped.startswith("'"):
            continue
        clean = re.sub(r"/\*.*?\*/", "", line)
        clean = re.sub(r"//.*", "", clean)
        clean = re.sub(r'"(?:[^"\\]|\\.)*"', '""', clean)
        clean = re.sub(r"'(?:[^'\\]|\\.)*'", "''", clean)
        for op in ("<=", ">=", "==", "!=", "&&", "||", "+", "-", "<", ">"):
            if op not in clean:
                continue
            if op in SKIP_EXTRA_OPS:
                continue
            if op in ("+", "-") and any(
                s in clean for s in ("++", "--", "+=", "-=")):
                continue
            out.append((i, op))
    return out


def mutate_line(line, op):
    opp = dict(OPS)
    token = opp[op]
    idx = line.find(op)
    while idx >= 0:
        if op in ("<=", ">=", "==", "!=", "&&", "||"):
            return line[:idx] + token + line[idx + len(op):]
        if op == "<" and idx + 1 < len(line) and line[idx + 1] == "=":
            idx = line.find(op, idx + 2)
            continue
        if op == ">" and idx + 1 < len(line) and line[idx + 1] == "=":
            idx = line.find(op, idx + 2)
            continue
        if op in ("<", ">") and idx > 0 and line[idx - 1] == "-":
            idx = line.find(op, idx + 1)
            continue
        if op in ("<", ">") and idx + 1 < len(line) and line[idx + 1] in "<>":
            idx = line.find(op, idx + 1)
            continue
        if op in ("+", "-") and idx + 1 < len(line) and line[idx + 1] in "+-=>":
            idx = line.find(op, idx + 1)
            continue
        if op in ("+", "-") and idx > 0 and line[idx - 1] in "+-":
            idx = line.find(op, idx + 1)
            continue
        if op in ("+", "-") and idx + 1 < len(line) and line[idx + 1].isdigit():
            idx = line.find(op, idx + 1)
            continue
        return line[:idx] + token + line[idx + 1:]
    return None


def find_modules(root):
    mods = []
    for name in sorted(os.listdir(os.path.join(root, "tests"))):
        m = re.fullmatch(r"test_(.+)\.c", name)
        if m and os.path.exists(os.path.join(root, "src", m.group(1) + ".c")):
            mods.append(m.group(1))
    return mods


def run_make(root, target):
    proc = subprocess.run(["make", "-s", target], cwd=root,
                          stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    return proc.returncode == 0


def run_bin(path):
    proc = subprocess.run([path], stdout=subprocess.DEVNULL,
                          stderr=subprocess.DEVNULL)
    return proc.returncode == 0


def main(argv):
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    args = [a for a in argv[1:] if a != "--verbose"]
    max_sites = MUTATE_MAX
    mods = None
    allow = []
    it = iter(args)
    for a in it:
        if a == "--max":
            max_sites = int(next(it))
        elif a == "--mods":
            mods = next(it).split(",")
        elif a == "--allow":
            allow = next(it).split(",")
    if mods is None:
        mods = find_modules(root)

    killed = []
    survived = []
    equivalent = []
    build_fail = []
    for mod in mods:
        src = os.path.join(root, "src", mod + ".c")
        if not os.path.exists(src):
            continue
        orig = open(src).read()
        sites = line_sites(orig)[:max_sites]
        for i, op in sites:
            lines = orig.split("\n")
            mutated = mutate_line(lines[i], op)
            if mutated is None:
                continue
            lines[i] = mutated
            label = "%s:%d %s->%s" % (mod, i + 1, op, dict(OPS)[op])
            try:
                open(src, "w").write("\n".join(lines))
                if not run_make(root, "build/test_" + mod):
                    build_fail.append(label)
                    continue
                if run_bin(os.path.join(root, "build", "test_" + mod)):
                    if label in allow:
                        equivalent.append(label)
                    else:
                        survived.append(label)
                else:
                    killed.append(label)
            finally:
                open(src, "w").write(orig)
        run_make(root, "build/test_" + mod)

    print("mutants killed:      %d" % len(killed))
    print("mutants survived:    %d" % len(survived))
    print("equivalent (allow):  %d" % len(equivalent))
    print("killed by -Werror:   %d" % len(build_fail))
    if survived:
        print()
        for s in survived:
            print("SURVIVED %s" % s)
        print()
        print("every survivor is a blind spot: add an assertion, then re-run")
        return 1
    print("all mutants died")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
