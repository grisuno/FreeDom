# `fuzz/fuzz_dom.c`

> Source: [fuzz/fuzz_dom.c:1](../../fuzz/fuzz_dom.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_dom_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_dom_h__dom_matches["dom.dom_matches"]
    n_src_dom_c__dom_closest["dom.dom_closest"]
    n_src_dom_c__dom_get_element_by_id["dom.dom_get_element_by_id"]
    n_src_dom_c__dom_query_selector["dom.dom_query_selector"]
    n_src_dom_c__dom_query_selector_all["dom.dom_query_selector_all"]
    n_fuzz_fuzz_dom_c__LLVMFuzzerTestOneInput -.-> n_include_dom_h__dom_matches
    n_fuzz_fuzz_dom_c__LLVMFuzzerTestOneInput -.-> n_src_dom_c__dom_closest
    n_fuzz_fuzz_dom_c__LLVMFuzzerTestOneInput -.-> n_src_dom_c__dom_get_element_by_id
    n_fuzz_fuzz_dom_c__LLVMFuzzerTestOneInput -.-> n_src_dom_c__dom_query_selector
    n_fuzz_fuzz_dom_c__LLVMFuzzerTestOneInput -.-> n_src_dom_c__dom_query_selector_all
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_dom.c:48](../../fuzz/fuzz_dom.c#L48)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`dom_matches`](include.dom.h.md#dom_matches), [`dom_closest`](src.dom.c.md#dom_closest), [`dom_get_element_by_id`](src.dom.c.md#dom_get_element_by_id), [`dom_query_selector`](src.dom.c.md#dom_query_selector), [`dom_query_selector_all`](src.dom.c.md#dom_query_selector_all)

---
