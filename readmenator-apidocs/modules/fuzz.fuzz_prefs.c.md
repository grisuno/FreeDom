# `fuzz/fuzz_prefs.c`

> Source: [fuzz/fuzz_prefs.c:1](../../fuzz/fuzz_prefs.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_prefs_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_prefs_h__free["prefs.free"]
    n_include_prefs_h__prefs_free["prefs.prefs_free"]
    n_include_prefs_h__prefs_init["prefs.prefs_init"]
    n_include_prefs_h__prefs_suggest["prefs.prefs_suggest"]
    n_src_prefs_c__prefs_bookmark_toggle["prefs.prefs_bookmark_toggle"]
    n_src_prefs_c__prefs_bookmarks_page["prefs.prefs_bookmarks_page"]
    n_src_prefs_c__prefs_format["prefs.prefs_format"]
    n_src_prefs_c__prefs_history_add["prefs.prefs_history_add"]
    n_src_prefs_c__prefs_parse["prefs.prefs_parse"]
    n_fuzz_fuzz_prefs_c__LLVMFuzzerTestOneInput -.-> n_include_prefs_h__free
    n_fuzz_fuzz_prefs_c__LLVMFuzzerTestOneInput -.-> n_include_prefs_h__prefs_free
    n_fuzz_fuzz_prefs_c__LLVMFuzzerTestOneInput -.-> n_include_prefs_h__prefs_init
    n_fuzz_fuzz_prefs_c__LLVMFuzzerTestOneInput -.-> n_include_prefs_h__prefs_suggest
    n_fuzz_fuzz_prefs_c__LLVMFuzzerTestOneInput -.-> n_src_prefs_c__prefs_bookmark_toggle
    n_fuzz_fuzz_prefs_c__LLVMFuzzerTestOneInput -.-> n_src_prefs_c__prefs_bookmarks_page
    n_fuzz_fuzz_prefs_c__LLVMFuzzerTestOneInput -.-> n_src_prefs_c__prefs_format
    n_fuzz_fuzz_prefs_c__LLVMFuzzerTestOneInput -.-> n_src_prefs_c__prefs_history_add
    n_fuzz_fuzz_prefs_c__LLVMFuzzerTestOneInput -.-> n_src_prefs_c__prefs_parse
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_prefs.c:21](../../fuzz/fuzz_prefs.c#L21)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`free`](include.prefs.h.md#free), [`prefs_free`](include.prefs.h.md#prefs_free), [`prefs_init`](include.prefs.h.md#prefs_init), [`prefs_suggest`](include.prefs.h.md#prefs_suggest), [`prefs_bookmark_toggle`](src.prefs.c.md#prefs_bookmark_toggle), [`prefs_bookmarks_page`](src.prefs.c.md#prefs_bookmarks_page), [`prefs_format`](src.prefs.c.md#prefs_format), [`prefs_history_add`](src.prefs.c.md#prefs_history_add), [`prefs_parse`](src.prefs.c.md#prefs_parse)

---
