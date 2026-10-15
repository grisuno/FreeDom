# `fuzz/fuzz_prefetch.c`

> Source: [fuzz/fuzz_prefetch.c:1](../../fuzz/fuzz_prefetch.c#L1) | language `c` | coverage 50.0% | [API index](../index.md)

libFuzzer harness for the prefetch lookahead scanner (Hito 29).

The scanned

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_prefetch_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_prefetch_h__pf_list_free["prefetch.pf_list_free"]
    n_include_prefetch_h__pf_scan["prefetch.pf_scan"]
    n_fuzz_fuzz_prefetch_c__LLVMFuzzerTestOneInput -.-> n_include_prefetch_h__pf_list_free
    n_fuzz_fuzz_prefetch_c__LLVMFuzzerTestOneInput -.-> n_include_prefetch_h__pf_scan
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_prefetch.c:10](../../fuzz/fuzz_prefetch.c#L10)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`pf_list_free`](include.prefetch.h.md#pf_list_free), [`pf_scan`](include.prefetch.h.md#pf_scan)

---
