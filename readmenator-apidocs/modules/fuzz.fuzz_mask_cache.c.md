# `fuzz/fuzz_mask_cache.c`

> Source: [fuzz/fuzz_mask_cache.c:1](../../fuzz/fuzz_mask_cache.c#L1) | language `c` | coverage 33.3% | [API index](../index.md)

libFuzzer harness for mask_cache (spec/mask_cache.md).

The input is a script of put/get

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)
- **Macros:** [`KEYS`](#keys)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_mask_cache_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_mask_cache_h__mkc_bytes["mask_cache.mkc_bytes"]
    n_include_mask_cache_h__mkc_clear["mask_cache.mkc_clear"]
    n_include_mask_cache_h__mkc_count["mask_cache.mkc_count"]
    n_include_mask_cache_h__mkc_free["mask_cache.mkc_free"]
    n_include_mask_cache_h__mkc_get["mask_cache.mkc_get"]
    n_include_mask_cache_h__mkc_new["mask_cache.mkc_new"]
    n_include_mask_cache_h__mkc_put["mask_cache.mkc_put"]
    n_fuzz_fuzz_mask_cache_c__LLVMFuzzerTestOneInput -.-> n_include_mask_cache_h__mkc_bytes
    n_fuzz_fuzz_mask_cache_c__LLVMFuzzerTestOneInput -.-> n_include_mask_cache_h__mkc_clear
    n_fuzz_fuzz_mask_cache_c__LLVMFuzzerTestOneInput -.-> n_include_mask_cache_h__mkc_count
    n_fuzz_fuzz_mask_cache_c__LLVMFuzzerTestOneInput -.-> n_include_mask_cache_h__mkc_free
    n_fuzz_fuzz_mask_cache_c__LLVMFuzzerTestOneInput -.-> n_include_mask_cache_h__mkc_get
    n_fuzz_fuzz_mask_cache_c__LLVMFuzzerTestOneInput -.-> n_include_mask_cache_h__mkc_new
    n_fuzz_fuzz_mask_cache_c__LLVMFuzzerTestOneInput -.-> n_include_mask_cache_h__mkc_put
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_mask_cache.c:21](../../fuzz/fuzz_mask_cache.c#L21)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`mkc_bytes`](include.mask_cache.h.md#mkc_bytes), [`mkc_clear`](include.mask_cache.h.md#mkc_clear), [`mkc_count`](include.mask_cache.h.md#mkc_count), [`mkc_free`](include.mask_cache.h.md#mkc_free), [`mkc_get`](include.mask_cache.h.md#mkc_get), [`mkc_new`](include.mask_cache.h.md#mkc_new), [`mkc_put`](include.mask_cache.h.md#mkc_put)

---

## Macros

<a id="keys"></a>

### `KEYS`

`macro` | [fuzz/fuzz_mask_cache.c:13](../../fuzz/fuzz_mask_cache.c#L13)

```c
#define KEYS
```

---
