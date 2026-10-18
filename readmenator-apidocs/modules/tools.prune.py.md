# `tools.prune`

> Source: [tools/prune.py:1](../../tools/prune.py#L1) | language `py` | coverage 50.0% | [API index](../index.md)

prune -- cut a corpus page down to ONE subtree, keeping its whole ancestor chain.

Isolating a layout bug on a 400 KB page by eye is slow; isolating it by deleting
everything that is not on the path to the element is mechanical. The <head> (every
<style> and <link>) is kept as is, so the cascade is untouched; in the <body> only the
target subtree and its ancestors survive, with every other sibling dropped along the
path. Scripts are removed (both engines render with JS off anyway).

Usage: prune.py <page.html> <xpath> <out.html>
  xpath  selects the element(s) to keep, e.g. '//nav[@class="nav-primary"]'
Prints the number of matched elements; exits 1 when none matched.

## Contents

- **Functions:** [`main`](#main)

## Functions

<a id="main"></a>

### `main`

`function` | [tools/prune.py:21](../../tools/prune.py#L21)

```python
def main()
```

---
