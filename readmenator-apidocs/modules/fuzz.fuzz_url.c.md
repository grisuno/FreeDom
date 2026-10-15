# `fuzz/fuzz_url.c`

> Source: [fuzz/fuzz_url.c:1](../../fuzz/fuzz_url.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_url_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_url_h__url_is_https["url.url_is_https"]
    n_src_css_color_c__strncmp["css_color.strncmp"]
    n_src_link_nav_c__ln_resolve["link_nav.ln_resolve"]
    n_src_url_c__url_history_target["url.url_history_target"]
    n_src_url_c__url_is_file["url.url_is_file"]
    n_src_url_c__url_split["url.url_split"]
    n_src_url_c__url_validate_https["url.url_validate_https"]
    n_fuzz_fuzz_url_c__LLVMFuzzerTestOneInput -.-> n_include_url_h__url_is_https
    n_fuzz_fuzz_url_c__LLVMFuzzerTestOneInput -.-> n_src_css_color_c__strncmp
    n_fuzz_fuzz_url_c__LLVMFuzzerTestOneInput -.-> n_src_link_nav_c__ln_resolve
    n_fuzz_fuzz_url_c__LLVMFuzzerTestOneInput -.-> n_src_url_c__url_history_target
    n_fuzz_fuzz_url_c__LLVMFuzzerTestOneInput -.-> n_src_url_c__url_is_file
    n_fuzz_fuzz_url_c__LLVMFuzzerTestOneInput -.-> n_src_url_c__url_split
    n_fuzz_fuzz_url_c__LLVMFuzzerTestOneInput -.-> n_src_url_c__url_validate_https
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_url.c:59](../../fuzz/fuzz_url.c#L59)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`url_is_https`](include.url.h.md#url_is_https), [`strncmp`](src.css_color.c.md#strncmp), [`ln_resolve`](src.link_nav.c.md#ln_resolve), [`url_history_target`](src.url.c.md#url_history_target), [`url_is_file`](src.url.c.md#url_is_file), [`url_split`](src.url.c.md#url_split), [`url_validate_https`](src.url.c.md#url_validate_https)

---
