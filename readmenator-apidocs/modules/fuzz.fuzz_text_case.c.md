# `fuzz/fuzz_text_case.c`

> Source: [fuzz/fuzz_text_case.c:1](../../fuzz/fuzz_text_case.c#L1) | language `c` | coverage 50.0% | [API index](../index.md)

libFuzzer harness for text_case (spec/text_case.md): case mapping and the

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_text_case_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_text_case_h__tc_smallcaps_runs["text_case.tc_smallcaps_runs"]
    n_include_text_case_h__tc_transform["text_case.tc_transform"]
    n_fuzz_fuzz_text_case_c__LLVMFuzzerTestOneInput -.-> n_include_text_case_h__tc_smallcaps_runs
    n_fuzz_fuzz_text_case_c__LLVMFuzzerTestOneInput -.-> n_include_text_case_h__tc_transform
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_text_case.c:13](../../fuzz/fuzz_text_case.c#L13)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`tc_smallcaps_runs`](include.text_case.h.md#tc_smallcaps_runs), [`tc_transform`](include.text_case.h.md#tc_transform)

---
