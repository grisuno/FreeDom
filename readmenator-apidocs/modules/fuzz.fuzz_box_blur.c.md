# `fuzz/fuzz_box_blur.c`

> Source: [fuzz/fuzz_box_blur.c:1](../../fuzz/fuzz_box_blur.c#L1) | language `c` | coverage 50.0% | [API index](../index.md)

libFuzzer harness for box_blur (spec/box_blur.md): a hostile mask, size, stride and sigma

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_box_blur_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_box_blur_h__bb_box_sizes["box_blur.bb_box_sizes"]
    n_src_box_blur_c__bb_blur_a8["box_blur.bb_blur_a8"]
    n_fuzz_fuzz_box_blur_c__LLVMFuzzerTestOneInput -.-> n_include_box_blur_h__bb_box_sizes
    n_fuzz_fuzz_box_blur_c__LLVMFuzzerTestOneInput -.-> n_src_box_blur_c__bb_blur_a8
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_box_blur.c:25](../../fuzz/fuzz_box_blur.c#L25)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`bb_box_sizes`](include.box_blur.h.md#bb_box_sizes), [`bb_blur_a8`](src.box_blur.c.md#bb_blur_a8)

---
