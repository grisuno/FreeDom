# `fuzz/fuzz_download.c`

> Source: [fuzz/fuzz_download.c:1](../../fuzz/fuzz_download.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_download_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_download_h__dl_should_download["download.dl_should_download"]
    n_src_css_color_c__strncmp["css_color.strncmp"]
    n_src_download_c__dl_build_path["download.dl_build_path"]
    n_src_download_c__dl_ext_for_type["download.dl_ext_for_type"]
    n_src_download_c__dl_pick_name["download.dl_pick_name"]
    n_fuzz_fuzz_download_c__LLVMFuzzerTestOneInput -.-> n_include_download_h__dl_should_download
    n_fuzz_fuzz_download_c__LLVMFuzzerTestOneInput -.-> n_src_css_color_c__strncmp
    n_fuzz_fuzz_download_c__LLVMFuzzerTestOneInput -.-> n_src_download_c__dl_build_path
    n_fuzz_fuzz_download_c__LLVMFuzzerTestOneInput -.-> n_src_download_c__dl_ext_for_type
    n_fuzz_fuzz_download_c__LLVMFuzzerTestOneInput -.-> n_src_download_c__dl_pick_name
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_download.c:31](../../fuzz/fuzz_download.c#L31)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`dl_should_download`](include.download.h.md#dl_should_download), [`strncmp`](src.css_color.c.md#strncmp), [`dl_build_path`](src.download.c.md#dl_build_path), [`dl_ext_for_type`](src.download.c.md#dl_ext_for_type), [`dl_pick_name`](src.download.c.md#dl_pick_name)

---
