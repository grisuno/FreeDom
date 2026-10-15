# `fuzz/fuzz_pdf_export.c`

> Source: [fuzz/fuzz_pdf_export.c:1](../../fuzz/fuzz_pdf_export.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_pdf_export_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_src_css_color_c__strncmp["css_color.strncmp"]
    n_src_pdf_export_c__pe_build_path["pdf_export.pe_build_path"]
    n_src_pdf_export_c__pe_safe_basename["pdf_export.pe_safe_basename"]
    n_fuzz_fuzz_pdf_export_c__LLVMFuzzerTestOneInput -.-> n_src_css_color_c__strncmp
    n_fuzz_fuzz_pdf_export_c__LLVMFuzzerTestOneInput -.-> n_src_pdf_export_c__pe_build_path
    n_fuzz_fuzz_pdf_export_c__LLVMFuzzerTestOneInput -.-> n_src_pdf_export_c__pe_safe_basename
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_pdf_export.c:30](../../fuzz/fuzz_pdf_export.c#L30)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`strncmp`](src.css_color.c.md#strncmp), [`pe_build_path`](src.pdf_export.c.md#pe_build_path), [`pe_safe_basename`](src.pdf_export.c.md#pe_safe_basename)

---
