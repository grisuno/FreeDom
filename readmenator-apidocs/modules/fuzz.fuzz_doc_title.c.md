# `fuzz/fuzz_doc_title.c`

> Source: [fuzz/fuzz_doc_title.c:1](../../fuzz/fuzz_doc_title.c#L1) | language `c` | coverage 50.0% | [API index](../index.md)

Fuzzer for doc_title (spec/doc_title.md): the title is always valid UTF-8, bounded by

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_doc_title_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_doc_title_h__dt_scan["doc_title.dt_scan"]
    n_fuzz_fuzz_doc_title_c__LLVMFuzzerTestOneInput -.-> n_include_doc_title_h__dt_scan
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_doc_title.c:26](../../fuzz/fuzz_doc_title.c#L26)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`dt_scan`](include.doc_title.h.md#dt_scan)

---
