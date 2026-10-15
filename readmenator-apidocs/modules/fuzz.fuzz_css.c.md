# `fuzz/fuzz_css.c`

> Source: [fuzz/fuzz_css.c:1](../../fuzz/fuzz_css.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_css_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_css_h__css_free["css.css_free"]
    n_src_css_c__css_parse["css.css_parse"]
    n_src_css_c__css_parse_inline["css.css_parse_inline"]
    n_src_css_c__css_parse_media["css.css_parse_media"]
    n_src_css_c__css_resolve["css.css_resolve"]
    n_src_css_c__css_resolve_el["css.css_resolve_el"]
    n_fuzz_fuzz_css_c__LLVMFuzzerTestOneInput -.-> n_include_css_h__css_free
    n_fuzz_fuzz_css_c__LLVMFuzzerTestOneInput -.-> n_src_css_c__css_parse
    n_fuzz_fuzz_css_c__LLVMFuzzerTestOneInput -.-> n_src_css_c__css_parse_inline
    n_fuzz_fuzz_css_c__LLVMFuzzerTestOneInput -.-> n_src_css_c__css_parse_media
    n_fuzz_fuzz_css_c__LLVMFuzzerTestOneInput -.-> n_src_css_c__css_resolve
    n_fuzz_fuzz_css_c__LLVMFuzzerTestOneInput -.-> n_src_css_c__css_resolve_el
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_css.c:80](../../fuzz/fuzz_css.c#L80)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`css_free`](include.css.h.md#css_free), [`css_parse`](src.css.c.md#css_parse), [`css_parse_inline`](src.css.c.md#css_parse_inline), [`css_parse_media`](src.css.c.md#css_parse_media), [`css_resolve`](src.css.c.md#css_resolve), [`css_resolve_el`](src.css.c.md#css_resolve_el)

---
