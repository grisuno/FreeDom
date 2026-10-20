# `tools.snapshot_age`

> Source: [tools/snapshot_age.py:1](../../tools/snapshot_age.py#L1) | language `py` | coverage 50.0% | [API index](../index.md)

Report parity snapshots older than N days (stamped by tools/snapshot.py).

Usage: snapshot_age.py PAGES_DIR MAX_DAYS
Exit 0 always: staleness is a warning, a page without a stamp predates the stamp and is
listed as `unstamped` so it can be re-frozen when it next matters.

## Contents

- **Functions:** [`main`](#main)
- **Constants:** [`STAMP`](#stamp)

## Functions

<a id="main"></a>

### `main`

`function` | [tools/snapshot_age.py:16](../../tools/snapshot_age.py#L16)

```python
def main()
```

---

## Constants

<a id="stamp"></a>

### `STAMP`

`constant` | [tools/snapshot_age.py:13](../../tools/snapshot_age.py#L13)

```python
STAMP = re.compile(b'<!-- freedom-snapshot url=(\\S+) date=(\\d{4}-\\d{2}-\\d{2}) -->')
```

---
