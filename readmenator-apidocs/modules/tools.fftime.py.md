# `tools.fftime`

> Source: [tools/fftime.py:1](../../tools/fftime.py#L1) | language `py` | coverage 50.0% | [API index](../index.md)

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
Prints one line per page:  <name>       <median ms>     <min>   <max>
Exit 0 when every page was measured; 1 on any failure (reported on stderr).

## Contents

- **Functions:** [`main`](#main)
- **Constants:** [`TIMELINE`](#timeline), [`PAINT_WAIT_S`](#paint_wait_s)

## Functions

<a id="main"></a>

### `main`

`function` | [tools/fftime.py:38](../../tools/fftime.py#L38)

```python
def main()
```

---

## Constants

<a id="timeline"></a>

### `TIMELINE`

`constant` | [tools/fftime.py:29](../../tools/fftime.py#L29)

```python
TIMELINE
```

---

<a id="paint_wait_s"></a>

### `PAINT_WAIT_S`

`constant` | [tools/fftime.py:35](../../tools/fftime.py#L35)

```python
PAINT_WAIT_S = 3.0
```

---
