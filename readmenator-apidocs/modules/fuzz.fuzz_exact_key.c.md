# `fuzz/fuzz_exact_key.c`

> Source: [fuzz/fuzz_exact_key.c:1](../../fuzz/fuzz_exact_key.c#L1) | language `c` | coverage 50.0% | [API index](../index.md)

libFuzzer harness for exact_key (spec/exact_key.md).

The input is split into two key

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_exact_key_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_exact_key_h__ek_equal["exact_key.ek_equal"]
    n_include_exact_key_h__ek_free["exact_key.ek_free"]
    n_include_exact_key_h__ek_init["exact_key.ek_init"]
    n_include_exact_key_h__ek_reset["exact_key.ek_reset"]
    n_include_exact_key_h__ek_swap["exact_key.ek_swap"]
    n_fuzz_fuzz_exact_key_c__LLVMFuzzerTestOneInput -.-> n_include_exact_key_h__ek_equal
    n_fuzz_fuzz_exact_key_c__LLVMFuzzerTestOneInput -.-> n_include_exact_key_h__ek_free
    n_fuzz_fuzz_exact_key_c__LLVMFuzzerTestOneInput -.-> n_include_exact_key_h__ek_init
    n_fuzz_fuzz_exact_key_c__LLVMFuzzerTestOneInput -.-> n_include_exact_key_h__ek_reset
    n_fuzz_fuzz_exact_key_c__LLVMFuzzerTestOneInput -.-> n_include_exact_key_h__ek_swap
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_exact_key.c:22](../../fuzz/fuzz_exact_key.c#L22)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`ek_equal`](include.exact_key.h.md#ek_equal), [`ek_free`](include.exact_key.h.md#ek_free), [`ek_init`](include.exact_key.h.md#ek_init), [`ek_reset`](include.exact_key.h.md#ek_reset), [`ek_swap`](include.exact_key.h.md#ek_swap)

---
