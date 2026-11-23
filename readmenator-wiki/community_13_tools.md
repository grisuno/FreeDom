# tools

*Community 13 | 2 files | cohesion 1.00*

## Definition

This community groups 2 file(s) rooted at `tools` with dominant language py (cohesion 1.00). Central symbols: `main`, `one_page`, `one_run`, `phase_ms`, `procs_display`, `start_display`. Core file: `tools/guiscroll.py` (4 symbols). Documented purpose: guiscroll -- what one frame costs in the REAL Freedom window while the user scrolls.  guitime measures "navigate -> painted and idle"; this measures the frames .

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tools/guiscroll.py` | py | utility | 4 | yes |
| `tools/guitime.py` | py | utility | 3 | yes |

## Key Symbols

- `phase_ms` (function, `tools/guiscroll.py:38`) `def phase_ms(line, phase)`
- `one_page` (function, `tools/guiscroll.py:48`) `def one_page(binary, page, env, prof, tmp, notches, hover)`
- `main` (function, `tools/guiscroll.py:95`) `def main()`
- `procs_display` (function, `tools/guiscroll.py:149`) `def procs_display(procs)` - The X display guitime.start_display put Xvfb on (it is the second process's argv).
- `start_display` (function, `tools/guitime.py:34`) `def start_display(workdir)` - Starts Xvfb and a nested weston; returns (env, processes) or None when unavailable.
- `one_run` (function, `tools/guitime.py:67`) `def one_run(binary, page, env, hosts_dir, tmp)`
- `main` (function, `tools/guitime.py:96`) `def main()`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 1
- Cross-boundary resolved imports (EXTRACTED): 0

## Connections

- No cross-community bridges recorded. This community is self-contained.

## Risks

- [taint high] `tools/guiscroll.py` -> `tools/guiscroll.py` via `subprocess` (0 hops)
- [taint high] `tools/guiscroll.py` -> `tools/guitime.py` via `subprocess` (1 hops)
- [taint high] `tools/guitime.py` -> `tools/guitime.py` via `subprocess` (0 hops)

## Open Questions

- Is the dangerous import `subprocess` in `tools/guiscroll.py` still required, or can it be isolated?
- What would break if the most connected file in tools changed?
- Should tools be split, given cohesion 1.00?

## Sources

- `tools/guiscroll.py`
- `tools/guitime.py`
