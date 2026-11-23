# `fuzz/fuzz_freebug.c`

> Source: [fuzz/fuzz_freebug.c:1](../../fuzz/fuzz_freebug.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_freebug_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_freebug_h__fb_buffer_count["freebug.fb_buffer_count"]
    n_include_freebug_h__fb_buffer_free["freebug.fb_buffer_free"]
    n_include_freebug_h__fb_buffer_init["freebug.fb_buffer_init"]
    n_include_freebug_h__fb_buffer_push_loc["freebug.fb_buffer_push_loc"]
    n_include_freebug_h__fb_buffer_reset["freebug.fb_buffer_reset"]
    n_src_freebug_c__fb_buffer_push["freebug.fb_buffer_push"]
    n_fuzz_fuzz_freebug_c__LLVMFuzzerTestOneInput -.-> n_include_freebug_h__fb_buffer_count
    n_fuzz_fuzz_freebug_c__LLVMFuzzerTestOneInput -.-> n_include_freebug_h__fb_buffer_free
    n_fuzz_fuzz_freebug_c__LLVMFuzzerTestOneInput -.-> n_include_freebug_h__fb_buffer_init
    n_fuzz_fuzz_freebug_c__LLVMFuzzerTestOneInput -.-> n_include_freebug_h__fb_buffer_push_loc
    n_fuzz_fuzz_freebug_c__LLVMFuzzerTestOneInput -.-> n_include_freebug_h__fb_buffer_reset
    n_fuzz_fuzz_freebug_c__LLVMFuzzerTestOneInput -.-> n_src_freebug_c__fb_buffer_push
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_freebug.c:37](../../fuzz/fuzz_freebug.c#L37)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`fb_buffer_count`](include.freebug.h.md#fb_buffer_count), [`fb_buffer_free`](include.freebug.h.md#fb_buffer_free), [`fb_buffer_init`](include.freebug.h.md#fb_buffer_init), [`fb_buffer_push_loc`](include.freebug.h.md#fb_buffer_push_loc), [`fb_buffer_reset`](include.freebug.h.md#fb_buffer_reset), [`fb_buffer_push`](src.freebug.c.md#fb_buffer_push)

---
