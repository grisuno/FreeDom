# `tools.ffq`

> Source: [tools/ffq.py:1](../../tools/ffq.py#L1) | language `py` | coverage 50.0% | [API index](../index.md)

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

## Contents

- **Functions:** [`main`](#main)

## Functions

<a id="main"></a>

### `main`

`function` | [tools/ffq.py:22](../../tools/ffq.py#L22)

```python
def main()
```

---
