# `tools.ffshot`

> Source: [tools/ffshot.py:1](../../tools/ffshot.py#L1) | language `py` | coverage 50.0% | [API index](../index.md)

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

## Contents

- **Functions:** [`main`](#main)

## Functions

<a id="main"></a>

### `main`

`function` | [tools/ffshot.py:24](../../tools/ffshot.py#L24)

```python
def main()
```

---
