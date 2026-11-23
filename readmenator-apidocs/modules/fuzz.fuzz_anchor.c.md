# `fuzz/fuzz_anchor.c`

> Source: [fuzz/fuzz_anchor.c:1](../../fuzz/fuzz_anchor.c#L1) | language `c` | coverage 50.0% | [API index](../index.md)

Fuzzer for anchor (spec/anchor.md) and url_split_location: a hostile document x a

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_anchor_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_anchor_h__anc_collect["anchor.anc_collect"]
    n_include_dom_h__dom_free["dom.dom_free"]
    n_include_dom_h__dom_get_attribute["dom.dom_get_attribute"]
    n_include_dom_h__dom_is_connected["dom.dom_is_connected"]
    n_include_html_parse_h__hp_document_free["html_parse.hp_document_free"]
    n_src_anchor_c__anc_resolve["anchor.anc_resolve"]
    n_src_dom_c__dom_build["dom.dom_build"]
    n_src_html_parse_c__hp_parse["html_parse.hp_parse"]
    n_fuzz_fuzz_anchor_c__LLVMFuzzerTestOneInput -.-> n_include_anchor_h__anc_collect
    n_fuzz_fuzz_anchor_c__LLVMFuzzerTestOneInput -.-> n_include_dom_h__dom_free
    n_fuzz_fuzz_anchor_c__LLVMFuzzerTestOneInput -.-> n_include_dom_h__dom_get_attribute
    n_fuzz_fuzz_anchor_c__LLVMFuzzerTestOneInput -.-> n_include_dom_h__dom_is_connected
    n_fuzz_fuzz_anchor_c__LLVMFuzzerTestOneInput -.-> n_include_html_parse_h__hp_document_free
    n_fuzz_fuzz_anchor_c__LLVMFuzzerTestOneInput -.-> n_src_anchor_c__anc_resolve
    n_fuzz_fuzz_anchor_c__LLVMFuzzerTestOneInput -.-> n_src_dom_c__dom_build
    n_fuzz_fuzz_anchor_c__LLVMFuzzerTestOneInput -.-> n_src_html_parse_c__hp_parse
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_anchor.c:37](../../fuzz/fuzz_anchor.c#L37)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`anc_collect`](include.anchor.h.md#anc_collect), [`dom_free`](include.dom.h.md#dom_free), [`dom_get_attribute`](include.dom.h.md#dom_get_attribute), [`dom_is_connected`](include.dom.h.md#dom_is_connected), [`hp_document_free`](include.html_parse.h.md#hp_document_free), [`anc_resolve`](src.anchor.c.md#anc_resolve), [`dom_build`](src.dom.c.md#dom_build), [`hp_parse`](src.html_parse.c.md#hp_parse)

---
