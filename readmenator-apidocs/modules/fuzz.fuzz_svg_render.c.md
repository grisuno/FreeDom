# `fuzz/fuzz_svg_render.c`

> Source: [fuzz/fuzz_svg_render.c:1](../../fuzz/fuzz_svg_render.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_svg_render_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_svg_render_h__sv_fit["svg_render.sv_fit"]
    n_src_svg_render_c__sv_parse["svg_render.sv_parse"]
    n_fuzz_fuzz_svg_render_c__LLVMFuzzerTestOneInput -.-> n_include_svg_render_h__sv_fit
    n_fuzz_fuzz_svg_render_c__LLVMFuzzerTestOneInput -.-> n_src_svg_render_c__sv_parse
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_svg_render.c:24](../../fuzz/fuzz_svg_render.c#L24)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`sv_fit`](include.svg_render.h.md#sv_fit), [`sv_parse`](src.svg_render.c.md#sv_parse)

---
