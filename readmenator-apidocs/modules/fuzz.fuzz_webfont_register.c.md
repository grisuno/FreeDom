# `fuzz/fuzz_webfont_register.c`

> Source: [fuzz/fuzz_webfont_register.c:1](../../fuzz/fuzz_webfont_register.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)
- **Macros:** [`FZ_GLYPHS`](#fz_glyphs)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_webfont_register_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_text_shape_h__tsh_measure["text_shape.tsh_measure"]
    n_include_text_shape_h__tsh_webfont_clear["text_shape.tsh_webfont_clear"]
    n_include_text_shape_h__tsh_webfont_register["text_shape.tsh_webfont_register"]
    n_include_webfont_h__wf_name_hash["webfont.wf_name_hash"]
    n_src_text_shape_c__tsh_shape["text_shape.tsh_shape"]
    n_fuzz_fuzz_webfont_register_c__LLVMFuzzerTestOneInput -.-> n_include_text_shape_h__tsh_measure
    n_fuzz_fuzz_webfont_register_c__LLVMFuzzerTestOneInput -.-> n_include_text_shape_h__tsh_webfont_clear
    n_fuzz_fuzz_webfont_register_c__LLVMFuzzerTestOneInput -.-> n_include_text_shape_h__tsh_webfont_register
    n_fuzz_fuzz_webfont_register_c__LLVMFuzzerTestOneInput -.-> n_include_webfont_h__wf_name_hash
    n_fuzz_fuzz_webfont_register_c__LLVMFuzzerTestOneInput -.-> n_src_text_shape_c__tsh_shape
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_webfont_register.c:26](../../fuzz/fuzz_webfont_register.c#L26)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`tsh_measure`](include.text_shape.h.md#tsh_measure), [`tsh_webfont_clear`](include.text_shape.h.md#tsh_webfont_clear), [`tsh_webfont_register`](include.text_shape.h.md#tsh_webfont_register), [`wf_name_hash`](include.webfont.h.md#wf_name_hash), [`tsh_shape`](src.text_shape.c.md#tsh_shape)

---

## Macros

<a id="fz_glyphs"></a>

### `FZ_GLYPHS`

`macro` | [fuzz/fuzz_webfont_register.c:24](../../fuzz/fuzz_webfont_register.c#L24)

```c
#define FZ_GLYPHS
```

---
