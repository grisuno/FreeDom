# `fuzz/fuzz_link_preview.c`

> Source: [fuzz/fuzz_link_preview.c:1](../../fuzz/fuzz_link_preview.c#L1) | language `c` | coverage 50.0% | [API index](../index.md)

Fuzzer for link_preview (spec/link_preview.md): input = base NUL href.

The status text

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_link_preview_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_src_link_nav_c__ln_resolve["link_nav.ln_resolve"]
    n_src_link_preview_c__lp_describe["link_preview.lp_describe"]
    n_fuzz_fuzz_link_preview_c__LLVMFuzzerTestOneInput -.-> n_src_link_nav_c__ln_resolve
    n_fuzz_fuzz_link_preview_c__LLVMFuzzerTestOneInput -.-> n_src_link_preview_c__lp_describe
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_link_preview.c:11](../../fuzz/fuzz_link_preview.c#L11)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`ln_resolve`](src.link_nav.c.md#ln_resolve), [`lp_describe`](src.link_preview.c.md#lp_describe)

---
