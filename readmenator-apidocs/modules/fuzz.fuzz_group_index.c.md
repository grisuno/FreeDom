# `fuzz/fuzz_group_index.c`

> Source: [fuzz/fuzz_group_index.c:1](../../fuzz/fuzz_group_index.c#L1) | language `c` | coverage 50.0% | [API index](../index.md)

libFuzzer harness for group_index (spec/group_index.md): random keys (including out-of-range ones) and key counts, checked against a naive per-key scan.

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_group_index_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_group_index_h__gi_build["group_index.gi_build"]
    n_fuzz_fuzz_group_index_c__LLVMFuzzerTestOneInput -.-> n_include_group_index_h__gi_build
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_group_index.c:9](../../fuzz/fuzz_group_index.c#L9)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`gi_build`](include.group_index.h.md#gi_build)

---
