# `tools.snapshot`

> Source: [tools/snapshot.py:1](../../tools/snapshot.py#L1) | language `py` | coverage 40.0% | [API index](../index.md)

Freeze a live page into one self-contained HTML file for `make parity`.

Both engines must render the SAME document offline (spec/parity.md), so every
same-site <link rel=stylesheet> is fetched once and inlined as <style>, and
scripts are dropped: parity runs JS off on both sides. Nothing else is fetched.

## Contents

- **Functions:** [`fetch`](#fetch), [`expand_imports`](#expand_imports), [`inline_css`](#inline_css), [`main`](#main)
- **Constants:** [`UA`](#ua), [`MAX_BYTES`](#max_bytes), [`IMPORT_RE`](#import_re), [`MAX_IMPORT_DEPTH`](#max_import_depth)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_tools_snapshot_py__inline_css(["inline_css"])
    n_tools_snapshot_py__expand_imports(["expand_imports"])
    n_tools_snapshot_py__main(["main"])
    n_tools_snapshot_py__inline_css --> n_tools_snapshot_py__expand_imports
    n_tools_snapshot_py__main --> n_tools_snapshot_py__inline_css
```

## Functions

<a id="fetch"></a>

### `fetch`

`function` | [tools/snapshot.py:18](../../tools/snapshot.py#L18)

```python
def fetch(url)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `url` |  |  |  |

---

<a id="expand_imports"></a>

### `expand_imports`

`function` | [tools/snapshot.py:32](../../tools/snapshot.py#L32)

```python
def expand_imports(css, base, depth)
```

Replace each @import with the imported text (wrapped in @media when the import carries a media condition), resolved against the SHEET url.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `css` |  |  |  |
| `base` |  |  |  |
| `depth` |  |  |  |

*Called by:* [`inline_css`](#inline_css)

---

<a id="inline_css"></a>

### `inline_css`

`function` | [tools/snapshot.py:49](../../tools/snapshot.py#L49)

```python
def inline_css(html, base)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `html` |  |  |  |
| `base` |  |  |  |

*Calls:* [`expand_imports`](#expand_imports)

*Called by:* [`main`](#main)

---

<a id="main"></a>

### `main`

`function` | [tools/snapshot.py:70](../../tools/snapshot.py#L70)

```python
def main()
```

*Calls:* [`inline_css`](#inline_css)

---

## Constants

<a id="ua"></a>

### `UA`

`constant` | [tools/snapshot.py:14](../../tools/snapshot.py#L14)

```python
UA = 'Mozilla/5.0 (X11; Linux x86_64; rv:128.0) Gecko/20100101 Firefox/128.0'
```

---

<a id="max_bytes"></a>

### `MAX_BYTES`

`constant` | [tools/snapshot.py:15](../../tools/snapshot.py#L15)

```python
MAX_BYTES = 8 * 1024 * 1024
```

---

<a id="import_re"></a>

### `IMPORT_RE`

`constant` | [tools/snapshot.py:26](../../tools/snapshot.py#L26)

```python
IMPORT_RE
```

---

<a id="max_import_depth"></a>

### `MAX_IMPORT_DEPTH`

`constant` | [tools/snapshot.py:29](../../tools/snapshot.py#L29)

```python
MAX_IMPORT_DEPTH = 4
```

---
