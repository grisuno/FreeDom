# `fuzz/fuzz_webfont.c`

> Source: [fuzz/fuzz_webfont.c:1](../../fuzz/fuzz_webfont.c#L1) | language `c` | coverage 50.0% | [API index](../index.md)

libFuzzer harness for the webfont lookahead scanner (spec/webfont.md).

The

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_webfont_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_webfont_h__wf_list_free["webfont.wf_list_free"]
    n_include_webfont_h__wf_scan["webfont.wf_scan"]
    n_fuzz_fuzz_webfont_c__LLVMFuzzerTestOneInput -.-> n_include_webfont_h__wf_list_free
    n_fuzz_fuzz_webfont_c__LLVMFuzzerTestOneInput -.-> n_include_webfont_h__wf_scan
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_webfont.c:11](../../fuzz/fuzz_webfont.c#L11)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`wf_list_free`](include.webfont.h.md#wf_list_free), [`wf_scan`](include.webfont.h.md#wf_scan)

---
